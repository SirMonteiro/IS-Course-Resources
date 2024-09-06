import java.io.PrintWriter;
import java.io.IOException;
import java.util.List;

public class GeradorDeRelatorios {

	public static final String ALG_INSERTIONSORT = "insertion";
	public static final String ALG_QUICKSORT = "quick";

	private List<Produto> produtos;
	private Sort algoritmo;
	private Criteria criterio;
	private Filter filtro;
	private String argFiltro;
	private boolean allBold;
	private boolean allItalic;

	public GeradorDeRelatorios(List<Produto> produtos, Sort algoritmo, Criteria criterio, Filter filtro,
			String argFiltro, boolean allBold, boolean allItalic) {

		this.produtos = produtos;
		this.algoritmo = algoritmo;
		this.criterio = criterio;
		this.filtro = filtro;
		this.argFiltro = argFiltro;
		this.allBold = allBold;
		this.allItalic = allItalic;
	}

	public void debug() {

		System.out.println("Gerando relatório para array contendo " + produtos.size() + " produto(s)");
		System.out.println("parametro filtro = '" + argFiltro + "'");
	}

	public void geraRelatorio(String arquivoSaida) throws IOException {

		debug();

		this.algoritmo.ordena(0, produtos.size() - 1, produtos, criterio);

		PrintWriter out = new PrintWriter(arquivoSaida);

		out.println("<!DOCTYPE html><html>");
		out.println("<head><title>Relatorio de produtos</title></head>");
		out.println("<body>");
		out.println("Relatorio de Produtos:");
		out.println("<ul>");

		int count = 0;

		for (Produto p : produtos) {
			if (this.filtro.filter(p, argFiltro)) {

				out.print("<li>");
				Format format = new FormatDefault();

				if (allBold)
					format = new FormatBold(format);

				if (allItalic)
					format = new FormatItalic(format);

				if (p instanceof ProductFormatted) {
					ProductFormatted pf = (ProductFormatted) p;
					if (pf.getBold() && !allBold)
						format = new FormatBold(format);
					if (pf.getItalic() && !allItalic)
						format = new FormatItalic(format);
					if (pf.getColor() != null)
						format = new FormatColor(format, pf.getColor());
				}
				format.format(out, p);
				out.println("</li>");
				count++;
			}
		}

		out.println("</ul>");
		out.println(count + " produtos listados, de um total de " + produtos.size() + ".");
		out.println("</body>");
		out.println("</html>");

		out.close();
	}

	public static void main(String[] args) {

		if (args.length < 4) {

			System.out.println("Uso:");
			System.out.println("\tjava " + GeradorDeRelatorios.class.getName()
					+ " <algoritmo> <critério de ordenação> <critério de filtragem> <parâmetro de filtragem> <opções de formatação>");
			System.out.println("Onde:");
			System.out.println("\talgoritmo: 'quick' ou 'insertion'");
			System.out.println("\tcriterio de ordenação: 'preco_c' ou 'descricao_c' ou 'estoque_c' ou 'preco_d' ou 'descricao_d' ou 'estoque_d'");
			System.out.println("\tcriterio de filtragem: 'todos' ou 'estoque_menor_igual' ou 'categoria_igual' ou 'preco_intervalo' ou 'descricao_contendo'");
			System.out.println("\tparâmetro de filtragem: argumentos adicionais necessários para a filtragem");
			System.out.println("\topções de formatação: 'negrito' e/ou 'italico'");
			System.out.println();
			System.exit(1);
		}

		String opcao_algoritmo = args[0];
		String opcao_criterio_ord = args[1];
		String opcao_criterio_filtro = args[2];
		String opcao_parametro_filtro = args[3];

		FilterEnum filterEnum = FilterEnum.getEnum(opcao_criterio_filtro);

		int formatLength = 2;

		int formatArgsStart = 4;
		if (filterEnum.equals(FilterEnum.FILTRO_TODOS)) {
			formatArgsStart--;
			formatLength++;
		}

		Boolean allBold = false;
		Boolean allItalic = false;

		if (args.length > formatArgsStart)
			for (int i = formatArgsStart; i < formatArgsStart + formatLength;) {
				switch (args[i]) {
					case "negrito":
						allBold = true;
						break;
					case "italico":
						allItalic = true;
						break;
				}

				if (args.length > i + 1)
					i++;
				else
					break;
			}

		Sort sort = null;
		switch (opcao_algoritmo) {

			case ALG_INSERTIONSORT:
				sort = new InsertionSort();
				break;
			case ALG_QUICKSORT:
				sort = new QuickSort();
				break;
			default:
				throw new RuntimeException("Algoritmo invalido!");
		}

		Criteria criteria = null;
		switch (CriteriaEnum.getEnum(opcao_criterio_ord)) {

			case CRIT_DESC_CRESC:
				criteria = new CriteriaDescriptionInc();
				break;
			case CRIT_PRECO_CRESC:
				criteria = new CriteriaPriceInc();
				break;
			case CRIT_ESTOQUE_CRESC:
				criteria = new CriteriaStockInc();
				break;
			case CRIT_DESC_DECRESC:
				criteria = new CriteriaDescriptionDec();
				break;
			case CRIT_PRECO_DECRESC:
				criteria = new CriteriaPriceDec();
				break;
			case CRIT_ESTOQUE_DECRESC:
				criteria = new CriteriaStockDec();
				break;
		}

		Filter filter = filterEnum.getFilter();

		GeradorDeRelatorios gdr = new GeradorDeRelatorios(new LoadProducts("produtos.csv").load(),
				sort,
				criteria,
				filter,
				opcao_parametro_filtro,
				allBold,
				allItalic);

		try {
			gdr.geraRelatorio("saida.html");
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}

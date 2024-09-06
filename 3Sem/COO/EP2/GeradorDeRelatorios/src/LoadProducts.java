import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class LoadProducts {
  private String fileName;

  public LoadProducts(String fileName) {
    this.fileName = fileName;
  }

  public List<Produto> load() {

		List<Produto> produtos = new ArrayList<>();

    try {
		Scanner sc = new Scanner(new File(this.fileName));
		sc.nextLine();
		sc.useDelimiter(", |\n");

		while (sc.hasNext()) {
			int id = sc.nextInt();
			String descricao = sc.next();
			String categoria = sc.next();
			int qtdEstoque = sc.nextInt();
			double preco = sc.nextDouble();
			boolean bold = sc.nextBoolean();
			boolean italic = sc.nextBoolean();
			String color = sc.next();
			produtos.add(new ProductFormatted(id, descricao, categoria, qtdEstoque, preco, bold, italic, color));
		}

		sc.close();
  } catch (IOException e) {
    e.printStackTrace();
  }
		return produtos;
	}

}

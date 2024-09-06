import java.io.PrintWriter;

public class FormatDefault implements Format{

  public void format(PrintWriter out, Produto p) {
    out.print(p.formataParaImpressao());
  }
}

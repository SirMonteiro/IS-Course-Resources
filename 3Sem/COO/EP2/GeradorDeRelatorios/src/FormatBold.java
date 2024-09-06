import java.io.PrintWriter;

public class FormatBold extends FormatDecorator{

  private Format format;

  protected FormatBold(Format format){
    super(format);
    this.format = format;
  }

  public void format(PrintWriter out, Produto p){
    out.print("<span style=\"font-weight:bold\">");
    this.format.format(out, p);
    out.print("</span>");
  }
}

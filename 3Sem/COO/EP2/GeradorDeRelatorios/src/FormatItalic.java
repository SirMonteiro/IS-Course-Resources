import java.io.PrintWriter;

public class FormatItalic extends FormatDecorator{

  private Format format;

  protected FormatItalic(Format format){
    super(format);
    this.format = format;
  }

  public void format(PrintWriter out, Produto p){
    out.print("<span style=\"font-style:italic\">");
    this.format.format(out, p);
    out.print("</span>");
  }
}

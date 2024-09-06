import java.io.PrintWriter;

public class FormatColor extends FormatDecorator{

  private Format format;
  private String color;

  protected FormatColor(Format format, String color){
    super(format);
    this.format = format;
    this.color = color;
  }

  public void format(PrintWriter out, Produto p){
    out.print("<span style=\"color:" + this.color + "\">");
    this.format.format(out, p);
    out.print("</span>");
  }
}

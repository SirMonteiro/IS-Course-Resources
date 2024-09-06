import java.io.PrintWriter;

public abstract class FormatDecorator implements Format{

  protected Format format;

  FormatDecorator(Format format){
    this.format = format;
  }

  public void format(PrintWriter out, Produto p) {
    this.format.format(out, p);
  }
}

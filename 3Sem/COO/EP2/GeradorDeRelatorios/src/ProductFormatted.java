public class ProductFormatted extends ProdutoPadrao {

  private boolean bold;
  private boolean italic;
  private String color;

  public ProductFormatted(int id, String descricao, String categoria, int qtdEstoque, double preco, boolean bold, boolean italic, String color) {
    super(id, descricao, categoria, qtdEstoque, preco);
    this.bold = bold;
    this.italic = italic;
    this.color = color;
  }

  // setters
  public void setBold(boolean bold) {
    this.bold = bold;
  }

  public void setItalic(boolean italic) {
    this.italic = italic;
  }

  public void setColor(String color) {
    this.color = color;
  }

  // getters
  public boolean getBold() {
    return this.bold;
  }

  public boolean getItalic() {
    return this.italic;
  }

  public String getColor() {
    return this.color;
  }
}

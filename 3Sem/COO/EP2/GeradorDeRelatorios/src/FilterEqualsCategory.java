public class FilterEqualsCategory implements Filter{
  public boolean filter(Produto p, String argFilter) {
    return p.getCategoria().equalsIgnoreCase(argFilter);
  }
}

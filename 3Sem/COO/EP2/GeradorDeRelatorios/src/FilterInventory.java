public class FilterInventory implements Filter{
  public boolean filter(Produto p, String argFilter) {
    return p.getQtdEstoque() <= Integer.parseInt(argFilter);
  }
}

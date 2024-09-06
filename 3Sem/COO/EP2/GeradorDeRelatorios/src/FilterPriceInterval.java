public class FilterPriceInterval implements Filter{
  public boolean filter(Produto p, String argFilter) {
    return p.getPreco() >= Double.parseDouble(argFilter.split(",")[0]) && p.getPreco() <= Double.parseDouble(argFilter.split(",")[1]);
  }
}

public class FilterDescription implements Filter {
  public boolean filter(Produto p, String argFilter) {
    return p.getDescricao().contains(argFilter);
  }
}

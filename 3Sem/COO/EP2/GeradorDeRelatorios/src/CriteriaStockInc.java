public class CriteriaStockInc implements Criteria{
  public boolean compare(Produto p1, Produto p2){
    return p1.getQtdEstoque() < p2.getQtdEstoque();
  }
}

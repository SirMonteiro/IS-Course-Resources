public class CriteriaPriceDec implements Criteria{
  public boolean compare(Produto p1, Produto p2){
    return p1.getPreco() > p2.getPreco();
  }

}

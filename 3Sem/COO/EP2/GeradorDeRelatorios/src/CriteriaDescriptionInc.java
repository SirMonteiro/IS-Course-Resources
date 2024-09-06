public class CriteriaDescriptionInc implements Criteria {
  public boolean compare(Produto p1, Produto p2){
    return p1.getDescricao().compareToIgnoreCase(p2.getDescricao()) < 0;
  }
}

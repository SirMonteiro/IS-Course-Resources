import java.util.Collections;
import java.util.List;

public class QuickSort implements Sort {
  private List<Produto> produtos;
  private Criteria criteria;

  public void ordena(int ini, int fim, List<Produto> produtos, Criteria criteria) {
    this.produtos = produtos;
    this.criteria = criteria;

    if (ini < fim)
    {
      int q = this.particiona(ini, fim);

      this.ordena(ini, q, produtos, criteria);
      this.ordena(q + 1, fim, produtos, criteria);
    }
  }

  private int particiona(int ini, int fim) {
    int i = (ini - 1);
    int j = (fim + 1);

    while (true) {

      do {
        j--;

      } while (criteria.compare(produtos.get(j), produtos.get(ini)));

      do {
        i++;

      } while (criteria.compare(produtos.get(ini), produtos.get(i)));

      if (i < j)
        Collections.swap(produtos, i, j);
      else
        break;
    }
    return j;
  }
}

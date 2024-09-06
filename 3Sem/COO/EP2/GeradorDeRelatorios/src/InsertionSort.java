import java.util.List;

public class InsertionSort implements Sort {

	public void ordena(int ini, int fim, List<Produto> produtos, Criteria criteria) {

		for (int i = ini; i <= fim; i++) {

			Produto x = produtos.get(i);
			int j = (i - 1);

			while (j >= ini) {

				if (criteria.compare(x, produtos.get(j))) {
					produtos.set(j + 1, produtos.get(j));
					j--;
				} else
					break;

				produtos.set(j + 1, x);
			}
		}
	}
}

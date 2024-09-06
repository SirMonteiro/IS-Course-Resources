public enum FilterEnum {
  FILTRO_TODOS("todos", new FilterAll()),
  FILTRO_ESTOQUE_MENOR_OU_IQUAL_A("estoque_menor_igual", new FilterInventory()),
  FILTRO_CATEGORIA_IGUAL_A("categoria_igual", new FilterEqualsCategory()),
  FILTRO_PRECO_INTERVALO("preco_intervalo", new FilterPriceInterval()),
  FILTRO_DESCRICAO_CONTENDO("descricao_contendo", new FilterDescription());

  private final String value;
  private final Filter filter;

  private FilterEnum(String value, Filter filter) {
    this.value = value;
    this.filter = filter;
  }

  public Filter getFilter() {
    return this.filter;
  }

  public static FilterEnum getEnum(String value) {
    for (FilterEnum filterEnum : values()) {
      if (filterEnum.value.equals(value)) {
        return filterEnum;
      }
    }
    throw new RuntimeException("Criterio de filtragem invalido!");
  }
}

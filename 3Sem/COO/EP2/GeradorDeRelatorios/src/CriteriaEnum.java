public enum CriteriaEnum {
  CRIT_DESC_CRESC("descricao_c"), CRIT_PRECO_CRESC("preco_c"), CRIT_ESTOQUE_CRESC("estoque_c"),
  CRIT_DESC_DECRESC("descricao_d"), CRIT_PRECO_DECRESC("preco_d"), CRIT_ESTOQUE_DECRESC("estoque_d");

  private String value;

  CriteriaEnum(String value) {
    this.value = value;
  }

  public static CriteriaEnum getEnum(String value) {
    for (CriteriaEnum critEnum : values()) {
      if (critEnum.value.equals(value)) {
        return critEnum;
      }
    }
    throw new RuntimeException("Criterio de ordenacao invalido!");
  }
}

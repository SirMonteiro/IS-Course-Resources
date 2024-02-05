    
    
    NO *p1 = NULL; // inicio 1
    NO *p2 = NULL; // inicio 2

    NO *p1no1 = (NO *)malloc(sizeof(NO));
    NO *p1no2 = (NO *)malloc(sizeof(NO));
    NO *p1no3 = (NO *)malloc(sizeof(NO));

    NO *p2no1 = (NO *)malloc(sizeof(NO));
    NO *p2no2 = (NO *)malloc(sizeof(NO));
    NO *p2no3 = (NO *)malloc(sizeof(NO));

    /* caso do pdf
    p1 = p1no1;
    p1no1->prox = p1no2;
    p1no2->prox = p1no3;
    p1no3->prox = p1no4;
    p1no4->prox = p1no5;
    p1no5->prox = NULL;

    p2 = p2no1;
    p2no1->prox = p2no2;
    p2no2->prox = p2no3;
    p2no3->prox = p1no3;

    p1no1->chave = 20;
    p1no2->chave = 30;
    p1no3->chave = 40;
    p1no4->chave = 90;
    p1no5->chave = 100;

    p2no1->chave = 200;
    p2no2->chave = 900;
    p2no3->chave = 300;
     */

    /* caso do pdf 2

 p1 = p1no1;
 p1no1->prox = p1no2;
 p1no2->prox = p1no3;
 p1no3->prox = p2no3;

 p2 = p2no1;
 p2no1->prox = p2no2;
 p2no2->prox = p2no3;
 p2no3->prox = p2no4;
 p2no4->prox = NULL;

 p1no1->chave = 20;
 p1no2->chave = 30;
 p1no3->chave = 40;

 p2no1->chave = 200;
 p2no2->chave = 900;
 p2no3->chave = 300;
 p2no4->chave = 800;

 */

    /* lista que se intercepta (1-2)

    p1 = p1no1;
    p1no1->prox = p2no1;

    p2 = p2no1;
    p2no1->prox = NULL;

    p1no1->chave = 10;
    p2no1->chave = 200;
    */

    /* lista que se intercepta (1-1)

    p1 = p1no1;
    p1no1->prox = NULL;

    p2 = p2no1;
    p2no1->prox = p1no1;

    p1no1->chave = 10;
    p2no1->chave = 200;
    */

    /* lista que se intercepta (0)

    p1 = p1no1;
    p1no1->prox = NULL;

    p2 = p1no1;

    p1no1->chave = 10;
    */

    /* listas que nunca se interceptam

    p1 = p1no1;
    p1no1->prox = p1no2;
    p1no2->prox = p1no3;
    p1no3->prox = NULL;

    p2 = p2no1;
    p2no1->prox = p2no2;
    p2no2->prox = p2no3;
    p2no3->prox = NULL;

    p1no1->chave = 20;
    p1no2->chave = 30;
    p1no3->chave = 40;

    p2no1->chave = 200;
    p2no2->chave = 900;
    p2no3->chave = 300;
    */
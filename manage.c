/*2020/05/02 HwangSuHwan
Make
addProduct(manage.h changed)
deleteProduct
updateProduct
*/

#include "manage.h"

void menu(){
	printf("*****재고 관리 프로그램*****\n");
	printf("1. 상품 추가\n");
	printf("2. 상품 정보 수정\n");
	printf("3. 상품 정보 삭제\n");
	printf("4. 제품의 재고 관리\n");
	printf("5. 상품 판매\n");
	printf("6. 상품 정보 출력\n");
	printf("7. 상품 정보 정렬\n");
	printf("8. 상품 정보 검색\n");
	printf("9. 상품 정보 저장\n");
	printf("10. 상품 정보 다시 불러오기\n");
	printf("0. 종료하기\n");
	printf("메뉴를 골라주세요!\n");
}

void addProduct(Product *p,int count){
	char temp[100];
	int EC=0; // errorcheck
	getchar();
	while(1){
		printf("상품의 이름을 입력해 주세요.");
		scanf("%[^\n]",temp);
		if(strlen(temp)<=50)break;
		printf("잘못된 입력입니다.\n");
		getchar();
	}
	strcpy(p[count].name,temp);
	getchar();
	while(1){
		printf("상품의 종류를 입력해 주세요.");
		scanf("%[^\n]",temp);
		if(strlen(temp)<=3)break;
		printf("잘못된 입력입니다.\n");
		getchar();
	}
	strcpy(p[count].category,temp);
	getchar();
	while(1){
		printf("상품의 가격을 입력해 주세요.");
		scanf("%[^\n]",temp);
		for(int i=0;i<strlen(temp);i++){
			if(temp[i]<48||57<temp[i]){
			EC=1;
			break;
			}
			else EC=0;
		}
		if(EC==0)break;
		printf("숫자 이외의 잘못된 입력 입니다.\n");
		getchar();
	}
	p[count].price=atoi(temp);
	getchar();
	while(1){
		printf("상품의 수량을 입력해 주세요.");
		scanf("%[^\n]",temp);
		for(int i=0;i<strlen(temp);i++){
			if(temp[i]<48||57<temp[i]){
			EC=1;
			break;
			}
			else EC=0;
		}
		if(EC==0)break;
		printf("숫자 이외의 잘못된 입력 입니다.\n");
		getchar();
	}
	p[count].quantity=atoi(temp);
	
}

void updateProduct(Product *p,int count){
	int select;
	for(;;){
		printf("수정을 원하는 제품의 번호를 입력해 주세요.");
		scanf("%d",&select);
		if(count<select)printf("잘못된 입력입니다. 다시 입력해주세요.\n");
		else break;
	}
	addProduct(p,select-1);
	printf("수정이 완료되었습니다.\n");
}
void deleteProduct(Product *p,int count){
	int select;
	int check=0;
	for(;;){
	printf("삭제를 원하는 제품의 번호를 입력해 주세요.");
	scanf("%d",&select);
		if(count<select)printf("잘못된 입력입니다. 다시 입력해주세요.\n");
		else break;
	}
	printf("정말 삭제를 하시겠습니까?(0.아니요 1.예 삭제하겠습니다)");
	scanf("%d",&check);
	if(check==1){
		p[select-1].price=-1;
		printf("삭제됨\n");
	}else{
		printf("취소됨\n");
	}
}
int loadData(Product p[]){
	int count=0;
	FILE*fp=fopen("list.txt","rt");
	if(fp==NULL){
		printf("저장된 파일이 없음.\n");
		fclose(fp);
		return 0;
	}
	for(;;count++){
		if(feof(fp))break;
		fscanf(fp,"%d %d %s %[^\n]",&p[count].price,&p[count].quantity,p[count].category,p[count].name);
		fgetc(fp);
		
	}
	count--;
	printf("%d 개의 항목이 로딩되었습니다.\n",count);
	return count;
}
void saveData(Product *p, int count){
	FILE *fp=fopen("list.txt","wt");
	for(int i=0;i<count;i++){
	if(p[i].price!=-1)
	fprintf(fp,"%d %d %s %s\n",p[i].price,p[i].quantity,p[i].category,p[i].name);	
	}
	printf("저장됨\n");
	fclose(fp);
}
int sellProduct(Product *p,int count){
	int money;
	int select;
	int qty; //quantity
	for(;;){
		printf("판매된 물건의 번호를 입력해 주세요.");
		scanf("%d",&select);
		if(count<select)printf("잘못된 입력입니다. 다시 입력해주세요.\n");
		else break;
	}
	select--;
	printf("해당 물건의 판매된 수량을 입력해 주세요.");
	scanf("%d",&qty);
	if(qty>p[select].quantity){
		printf("판매 수량이 재고를 초과하였습니다.\n");
		return 0;
	}
	p[select].quantity-=qty;
	money=p[select].price*qty;
	printf("%s의 수량이 %d 만큼 감소하고, %d만큼의 수입이 생겼습니다.\n",p[select].name,qty,money);
	return money;	
}

void updateQuantity(Product *p,int count){
	int select;
	int nquantity;
	for(;;){
		printf("재고를 수정할 상품의 번호를 입력해 주세요.");
		scanf("%d",&select);
		if(count<select)printf("잘못된 입력입니다. 다시 입력해주세요.\n");
		else break;
	}
	select--;
	printf("현제 해당 제품의 재고: %d\n",p[select].quantity);
	for(;;){
		printf("수정하려는 재고 량을 입력해주세요:");
		scanf("%d",&nquantity);
		if(nquantity<0){
			printf("잘못된 수량 입니다. 다시 입력해주세요.\n");
		}else{
			p[select].quantity=nquantity;
			printf("수정되었습니다.\n");
			break;
		}
	}
}

#include<stdio.h>
#include<windows.h>
//ȫ�ֱ���
int qipan[15][15];
int winWays[15][15][572];
int whileWin[572]; //������������������˶��ٸ�����
int blackWin[572];//������������������˶��ٸ�����
int cou=0;//���������������
int first=0;//��û�����¿�ʼ��0Ϊû��
int isFlag=1;//1��ʾ��ûӮ
int isVictor();//�ж�ʤ�� 
int color=1;//0��ʾ����(ԲȦ)��1��ʾ����
void drawQiPan();//������ 
void init();//��ʼ�� 
void allWinWays();//����Ӯ�ķ�ʽ 
void computerAI();//�������� 
void nextChess(); //���� 
/*************************************************
     *
     *���Ʊ����Ҫ���ַ�:�� �� ���� �� �ȩ� �� ���������
     *�����ֵ0��ʾ���壬1��ʾ���壬2��ʾ��λ��û����
     *
     */
int main(){


    int i,j;//��ʾ���̺�������
	int mode=1;//ѡ��ģʽ 
    int op=0;
    do{
        init();
        printf("��ѡ��ģʽ�� 1 �˻�ģʽ    2 ˫��ģʽ     (���������˳�)\n");
        scanf("%d", &mode);
        if(mode!=1 && mode!=2)
		continue;//�����������λ���˳� 
        
        do{
            printf("����������λ�ã����̴�СΪ15*15),��2 2: ");
            scanf("%d %d", &i,&j);
            if(i<0 && i >=15 || j<0 || j>=15){
                printf("�����λ�ó��������̵ķ�Χ�����������룡\n");
                continue;
            }
            if((2 != qipan[i][j])){
                printf("��ʾ����λ���Ѿ���������!\n");
       
                continue;
            }

       
            qipan[i][j]=color;//����λ�ð��������Ը�����

        //�ж���Ӯ
            if(1==isVictor()){
                isFlag=1;
            }else{
                if(mode==1){
                    computerAI();
                }else{
                    drawQiPan();
                    nextChess();
                }

                isFlag=isVictor();
//			printf("%d \n",isFlag);
            }
		//�������̶�Ӧλ�����ԣ���������״̬�����̣�һ���л��ƣ���Ե�ر���
            drawQiPan();
        }while(isFlag==0);//������Ӯ�˾ͽ���ѭ�� 
        printf("���¿�ʼ�������˳�?���¿�ʼ�밴1,�˳��밴0\n");
        scanf("%d",&op);

        if(1 == op){
    	system("cls");
        printf("�Ѿ����¿�ʼ�ˣ�\n");
        first=1;
        }
	}while(1 == op);
}

//�ж��Ƿ���һ��Ӯ�ˣ�����ӡ����һ��Ӯ��
int isVictor(){
	int i,j,k;
	int flag=0;

	//��ʼ��
	for(i=0;i<cou;i++){ //counalai??????????
           blackWin[i]=0;
           whileWin[i]=0;
    }

	for(i=0;i<15;i++) {
        for (j = 0; j < 15; j++) {
            if(qipan[i][j]==1){//��λ��Ϊ����ʱ
                for(k=0;k<cou;k++){
                    if (winWays[i][j][k]==3){
                        whileWin[k]++;
                        blackWin[k]=6;//���ﲻ�������γ������飬������������ٿ���
                        if(5==whileWin[k]){
							printf("����Ӯ��\n");
							flag=1;
							break;
						}
//					printf("%d  %d \n",myWin[k],k);
                    }
                }
            }
            if(qipan[i][j]==0){
                for(k=0;k<cou;k++){
                    if (winWays[i][j][k]==3){
                        whileWin[k]=6;//���ﲻ�������γ������飬������������ٿ���
                        blackWin[k]++;
						if(5==blackWin[k]){
							printf("����Ӯ��\n");
							flag=1;
							break;
						}
                    }
                }
            }
        }
    }

	return flag;
}

//��ʼ��:���̣�1Ϊ���� 0Ϊ���壬2Ϊ��;�������ʼ��:ֻ���ڳ�������ʱ��ʼ��һ��
void init(){
	int i=0,j=0,isFlag=1,color=1;
	for(i=0;i<15;i++){
        for(j=0;j<15;j++){
			qipan[i][j]=2;
			}
	}
	if(first==0){
		allWinWays();//�����������������������¼����ά������ 
	}

}
void allWinWays(){
	int i,j,k;
	//����ά������ȫ��Ӯʱ�����������
	for(i = 0; i < 15; i++) {         //�������·���Ӯ���Ĵ���
        for (j = 0; j < 15-4; j++) {
            for ( k = 0; k < 5; k++) {
                   winWays[i][j+k][cou] = 3;
               }
               cou++;

           }
    }

    for(i = 0; i < 15; i++) {      //�������ҷ���Ӯ���Ĵ���
        for (j = 0; j < 15-4; j++) {
            for (k = 0; k < 5; k++) {
                winWays[j+k][i][cou] = 3;
	        }
	         cou++;

        }
	}
    for(i = 0; i < 15-4; i++) {      //�����������Ϸ���Ӯ���Ĵ���
        for (j = 0; j < 15-4; j++) {
            for (k = 0; k < 5; k++) {
                winWays[i+k][j+k][cou] = 3;
            }
                cou++;
           }
    }
    for(i = 0; i < 15-4; i++) {       //������������Ӯ���Ĵ���
    	for (j = 15; j > 4; j--) {
            for (k = 0; k < 5; k++) {
                winWays[i+k][j-k][cou] = 3;
            }
             cou++;
        }
    }
}

void nextChess(){//������ 
	int i,j;
	int flag=1;
	do{

	printf("����������λ�ã����̴�СΪ15*15),��2 2: ");
        scanf("%d %d", &i,&j);
        if(i<0 || i >15 || j<0 || j>15){
            printf("�����λ�ó��������̵ķ�Χ�����������룡\n");
            continue;
        }
        else if((2 != qipan[i][j])){
            printf("��ʾ����λ���Ѿ���������!\n");
         //  fflush(stdin);
            continue;
       	}else{
       		flag=0;
		   }
	}while(flag==1);
        color=(color+1)%2;//��ȡ������������
        qipan[i][j]=color;//����λ���������Ը�����
        color=(color+1)%2;
}



//���Ժ��֣�����ִ��
void computerAI(){
	int i,j,k;
	int myScore[15][15];//�������ϵķ���
    int computerScore[15][15];
	int max_Score=0;
    int row=0,column=0;//����

	for(i=0;i<15;i++){
        for(j=0;j<15;j++){
           	myScore[i][j]=0;
            computerScore[i][j]=0;
        }
    }
    for(i=0;i<15;i++){
        for(j=0;j<15;j++){
            if(qipan[i][j]==2){//�ж�������û���ӣ� ���û�к��Ӳſ�����
                for(k=0;k<cou;k++){
                    if(winWays[i][j][k]==3){//��ѯ������ȫ������������
                        if(whileWin[k]==1){//�����������������£���һ���� 
                            myScore[i][j]+=200;
						}else if(whileWin[k]==2){//�����������������£��ж����� 
                            myScore[i][j]+=400;
                        }else if(whileWin[k]==3){
                            myScore[i][j]+=4000;
                        }else if(whileWin[k]==4){
                            myScore[i][j]+=50000;
                        }
                        if(blackWin[k]==1){//�����������������£����������������һ����
                            computerScore[i][j]+=320;
                        }else if(blackWin[k]==2){
                            computerScore[i][j]+=420;
                        }else if(blackWin[k]==3){
                            computerScore[i][j]+=4200;
                        }else if(blackWin[k]==4){
                            computerScore[i][j]+=52000;
                        }
                    }
                }
				if(myScore[i][j]>max_Score){
                    max_Score=myScore[i][j];
                    row=i;
                    column=j;
                }else if(myScore[i][j]==max_Score){
                    if(computerScore[i][j]>computerScore[row][column]){
                        row=i;
                        column=j;
                    }
                }

                if(computerScore[i][j]>max_Score){
                    max_Score=computerScore[i][j];
                    row=i;
                    column=j;
                }else if(computerScore[i][j]==max_Score){
                    if(myScore[i][j]>computerScore[row][column]){
                        row=i;
                        column=j;
                    }
                }
			}
        }
    }
    printf("���������ˣ�%d  %d \n",row,column);
	qipan[row][column]=0;

}



//����15*15����,���������µ�����
void drawQiPan(){
		int i=0,j=0;
	for(i=0;i<15;i++){
            //��һ��
		if(i==0){
			printf(" 0  1 2 3 4 5 6 7 8 91011121314\n");//��ӡ��������� 
            //��һ��
            if(qipan[i][0]==1)
                printf("  ��");
            if(qipan[i][0]==0)
                printf("  ��");
            if(qipan[i][0]==2)
            
                printf("  ��");

            //��2-14��
            for(j=1;j<14;j++){
                if(qipan[i][j]==1)
                    printf("��");
                if(qipan[i][j]==0)
                    printf("��");
                if(qipan[i][j]==2&&i==0){

				printf("��");
				}
            }

        	//��15��
            if(qipan[i][j]==1)
                printf("��");
            if(qipan[i][j]==0)
                printf("��");
            if(qipan[i][j]==2)
                printf("��");

            printf("\n");
        }

            //��2-14��
        if(i<14 && i>=1){
            //��һ��
			printf("%d",i);
            if(i<10)//����1-13���� 
            	printf(" ");
            if(qipan[i][0]==1)
                printf("��");
            if(qipan[i][0]==0)
                printf("��");
            if(qipan[i][0]==2)
                
                     printf("��");

                //��2-14��
            for(j=1;j<14;j++){
                if(qipan[i][j]==1)
                    printf("��");
                if(qipan[i][j]==0)
                    printf("��");
                if(qipan[i][j]==2)
                    printf("��");
            }

            //��15��
			if(qipan[i][j]==1)
                printf("��");
            if(qipan[i][j]==0)
                printf("��");
            if(qipan[i][j]==2)
                printf("��");

                printf("\n");
        }

        //��15��
        if(i==14){
        	//��һ�� 
			printf("14");
            if(qipan[i][0]==1)
                printf("��");
            if(qipan[i][0]==0)
                printf("��");
            if(qipan[i][0]==2)
                
				printf("��");

            for(j=1;j<14;j++){
                if(qipan[i][j]==1)
                    printf("��");
                if(qipan[i][j]==0)
                    printf("��");
                if(qipan[i][j]==2)
                    printf("��");
            }

            if(qipan[i][j]==1)
                printf("��");
            if(qipan[i][j]==0)
                printf("��");
            if(qipan[i][j]==2)
                printf("��");

            printf("\n");
        }
	 }
}





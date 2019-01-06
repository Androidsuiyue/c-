#include<stdio.h>
#include<windows.h>
//全局变量
int qipan[15][15];
int winWays[15][15][572];
int whileWin[572]; //白棋在哪种情况下连了多少个棋子
int blackWin[572];//黑棋在哪种情况下连了多少个棋子
//多少种五连珠情况
int cou=0;
//有没有重新开始，0为没有
int first=0;
int isFlag=1;//1表示还没赢
int isVictor();
int color=1;//0表示黑棋(圆圈)，1表示白棋
void drawQiPan();
void init();
void allWinWays();
void computerAI();
void nextChess(); 
/*************************************************
     *
     *绘制表格需要的字符:┌ ┬ ┐├ ┼ ┤└ ┴ ┘│─●○
     *数组的值0表示黑棋，1表示白棋，2表示该位置没有棋
     *
     */
int main(){


    int i,j;//表示棋盘横纵坐标
	int mode=1;
    int op=0;
    do{
        init();
        printf("请选择模式： 1 人机模式    2 双人模式\n");
        scanf("%d", &mode);
        do{
            printf("请输入棋子位置（棋盘大小为15*15),如2 2: ");
            scanf("%d %d", &i,&j);
            if(i<1 || i >15 || j<1 || j>15){
                printf("输入的位置超出了棋盘的范围，请重新输入！\n");
                continue;
            }
            if((2 != qipan[i][j])){
                printf("提示：该位置已经有棋子了!\n");
         //  fflush(stdin);
                continue;
            }

       // color=(color+1)%2;//获取棋盘棋子属性
            qipan[i][j]=color;//将该位置棋子属性给棋盘

        //判断输赢
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
		//根据棋盘对应位置属性，绘制最新状态的棋盘，一行行绘制，边缘特别处理
            drawQiPan();
        }while(isFlag==0);
        printf("重新开始，还是退出?重新开始请按1,退出请按0\n");
        scanf("%d",&op);
//    op = getchar();
        if(1 == op){
    	system("cls");
        printf("已经重新开始了，\n");
        first=1;
        }
    }while(1 == op);
}

//判断是否有一方赢了，并打印出哪一方赢了
int isVictor(){
	int i,j,k;
	int flag=0;

	//初始化
	for(i=0;i<cou;i++){
           blackWin[i]=0;
           whileWin[i]=0;
    }

	for(i=0;i<15;i++) {
        for (j = 0; j < 15; j++) {
            if(qipan[i][j]==1){//这位置为白棋时
                for(k=0;k<cou;k++){
                    if (winWays[i][j][k]==3){
                        whileWin[k]++;
                        blackWin[k]=6;//这里不可以能形成五连珠，把这种情况不再考虑
                        if(5==whileWin[k]){
							printf("白棋赢了\n");
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
                        whileWin[k]=6;//这里不可以能形成五连珠，把这种情况不再考虑
                        blackWin[k]++;
						if(5==blackWin[k]){
							printf("黑棋赢了\n");
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

//初始化:棋盘，1为白棋 0为黑棋，2为空;五连珠初始化:只有在程序运行时初始化一次
void init(){
	int i=0,j=0,isFlag=1,color=1;
	for(i=0;i<15;i++){
        for(j=0;j<15;j++){
			qipan[i][j]=2;
			}
	}
	if(first==0){
		allWinWays();
	}

}
void allWinWays(){
	int i,j,k;
	//用三维数组存放全部赢时五连珠的坐标
	for(i = 0; i < 15; i++) {         //计算上下方向赢法的次数
        for (j = 0; j < 15-4; j++) {
            for ( k = 0; k < 5; k++) {
                   winWays[i][j+k][cou] = 3;
               }
               cou++;
//			   printf("%d \n",cou);
           }
    }

    for(i = 0; i < 15; i++) {      //计算左右方向赢法的次数
        for (j = 0; j < 15-4; j++) {
            for (k = 0; k < 5; k++) {
                winWays[j+k][i][cou] = 3;
	        }
	         cou++;
//			 printf("%d \n",cou);
        }
	}
    for(i = 0; i < 15-4; i++) {      //计算左下右上方向赢法的次数
        for (j = 0; j < 15-4; j++) {
            for (k = 0; k < 5; k++) {
                winWays[i+k][j+k][cou] = 3;
            }
                cou++;
           }
    }
    for(i = 0; i < 15-4; i++) {       //计算左上右下赢法的次数
    	for (j = 15; j > 4; j--) {
            for (k = 0; k < 5; k++) {
                winWays[i+k][j-k][cou] = 3;
            }
             cou++;
        }
    }
}

void nextChess(){
	int i,j;
	int flag=1;
	do{

	printf("请输入棋子位置（棋盘大小为15*15),如2 2: ");
        scanf("%d %d", &i,&j);
        if(i<1 || i >15 || j<1 || j>15){
            printf("输入的位置超出了棋盘的范围，请重新输入！\n");
            continue;
        }
        else if((2 != qipan[i][j])){
            printf("提示：该位置已经有棋子了!\n");
         //  fflush(stdin);
            continue;
       	}else{
       		flag=0;
		   }
	}while(flag==1);
        color=(color+1)%2;//获取棋盘棋子属性
        qipan[i][j]=color;//将该位置棋子属性给棋盘
        color=(color+1)%2;
}



//电脑后手，电脑执黑
void computerAI(){
	int i,j,k;




	int myScore[15][15];//下棋盘上的分数
    int computerScore[15][15];
	int max_Score=0;
    int row=0,column=0;//坐标

	for(i=0;i<15;i++){
        for(j=0;j<15;j++){
           	myScore[i][j]=0;
            computerScore[i][j]=0;
        }
    }
    for(i=0;i<15;i++){
        for(j=0;j<15;j++){
            if(qipan[i][j]==2){//判断这里有没棋子， 如果没有黑子才可以下
                for(k=0;k<cou;k++){
                    if(winWays[i][j][k]==3){//查询出这里全部五连珠的情况
                        if(whileWin[k]==1){//如果
                            myScore[i][j]+=200;
						}else if(whileWin[k]==2){
                            myScore[i][j]+=400;
                        }else if(whileWin[k]==3){
                            myScore[i][j]+=4000;
                        }else if(whileWin[k]==4){
                            myScore[i][j]+=50000;
                        }
                        if(blackWin[k]==1){
                            computerScore[i][j]+=320;
                        }else if(blackWin[k]==2){
                            computerScore[i][j]+=420;
                        }else if(blackWin[k]==3){
                            computerScore[i][j]+=4200;
                        }else if(blackWin[k]==4){
                            computerScore[i][j]+=50000;
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
    printf("电脑下在了：%d  %d \n",row,column);
	qipan[row][column]=0;

}



//绘制15*15棋盘,并画出最新的棋子
void drawQiPan(){
	int i=0,j=0;
	for(i=1;i<=15;i++){
            //第一行
		if(i==1){
            //第一列
            if(qipan[i-1][0]==1)
                printf("●");
            if(qipan[i-1][0]==0)
                printf("○");
            if(qipan[i-1][0]==2)
                printf("┌ ");

            //第2-14列
            for(j=2;j<15;j++){
                if(qipan[i-1][j-1]==1)
                    printf("●");
                if(qipan[i-1][j-1]==0)
                    printf("○");
                if(qipan[i-1][j-1]==2&&i==1){

				printf("┬ ");
				}
            }

        	//第15列
            if(qipan[i-1][j-1]==1)
                printf("●");
            if(qipan[i-1][j-1]==0)
                printf("○");
            if(qipan[i-1][j-1]==2)
                printf("┐ ");

            printf("\n");
        }

            //第2-14行
        if(i<15 && i>=2){
            //第一列
            if(qipan[i-1][0]==1)
                printf("●");
            if(qipan[i-1][0]==0)
                printf("○");
            if(qipan[i-1][0]==2)
                printf("├ ");

                //第2-14列
            for(j=2;j<15;j++){
                if(qipan[i-1][j-1]==1)
                    printf("●");
                if(qipan[i-1][j-1]==0)
                    printf("○");
                if(qipan[i-1][j-1]==2)
                    printf("┼ ");
            }

            //第15列
			if(qipan[i-1][j-1]==1)
                printf("●");
            if(qipan[i-1][j-1]==0)
                printf("○");
            if(qipan[i-1][j-1]==2)
                printf("┤ ");

                printf("\n");
        }

        //第15行
        if(i==15){
            if(qipan[i-1][0]==1)
                printf("●");
            if(qipan[i-1][0]==0)
                printf("○");
            if(qipan[i-1][0]==2)
                printf("└ ");

            for(j=2;j<15;j++){
                if(qipan[i-1][j-1]==1)
                    printf("●");
                if(qipan[i-1][j-1]==0)
                    printf("○");
                if(qipan[i-1][j-1]==2)
                    printf("┴ ");
            }

            if(qipan[i-1][j-1]==1)
                printf("●");
            if(qipan[i-1][j-1]==0)
                printf("○");
            if(qipan[i-1][j-1]==2)
                printf("┘ ");

            printf("\n");
        }
	 }
}





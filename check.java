import java.util.*;

public class Main{


        public static void main(String args[]){

                Scanner sc = new Scanner(System.in);

                //入力
                int country_count = sc.nextInt();
                int i=0;
                int j=0;
                int data[][] = new int[country_count][3];
                for(i=0;i<country_count;i++){

                        for(j=0;j<3;j++){

                                data[i][j] = sc.nextInt();
                                //System.out.print(data[i][j] + " ");
                        }
                        //System.out.println("");


                }

                //アルゴリズム
                int k=0;
                int max=0;
                int s=0;
                int t=0;
                int tmp=0;
                int mode=0;
                for(i=0;i<country_count-1;i++){


                        max = data[i][k];
                        for(j=i+1;j<country_count;j++){

                                if(max<data[j][k]){
                                        //第2位でソートし始めてしまっている
                                        //交換

                                        k=0;
                                        max = data[j][k];

                                        for(s=0;s<3;s++){

                                                tmp = data[j][s];
                                                data[j][s] = data[i][s];
                                                data[i][s] = tmp;

                                        }


                                        //確認出力
                                        System.out.println("---------------------");
                                        for(s=0;s<country_count;s++){

                                                for(t=0;t<3;t++){

                                                        System.out.print(data[s][t]+" ");

                                                }
                                                System.out.println("");
                                        }
                                        System.out.println("----------------------");


                                }else if(max==data[j][k]){
                                        
                                        k++;
                                        j--;
                                        max = data[i][k];
                                        if(k==2){
                                                //同じものがある
                                                k=0;

                                        }else{

                                        }

                                }else{
                                        //位置を変える必要はない

                                }

                        }
                        System.out.println(( i+1)+" round end" );
                }


                //出力
                for(i=0;i<country_count;i++){

                        for(j=0;j<3;j++){
                        
                                System.out.print(data[i][j]);

                                if(j!=2){
                                        System.out.print(" ");

                                }else{

                                }

                        }
                        if(i!=country_count-1){
                                        
                                System.out.print("\n");

                        }else{

                        }
                }
                
        }
}

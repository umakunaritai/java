import java.util.*;

public class Main{

        public static void main(String args[]){

                Scanner sc = new Scanner(System.in);

                //入力
                int count=sc.nextInt();
                int i=0;
                int j=0;
                int array[][] = new int[count][3];
                for(i=0;i<count;i++){

                        for(j=0;j<3;j++){
                                
                                array[i][j] = sc.nextInt();

                        }

                }
                //アルゴリズム
                int max = array[0][0];
                int k=0;
                int s=0;
                int t=0;
                int tmp=0;
                for(i=0;i<count-1;i++){

                        //System.out.println( (i+1)+"th round start");
                        max = array[i][k];
                        for(j=i+1;j<count;j++){

                                //確認出力
                                //System.out.println("comparing max:" + max +" array[j][k]:"+array[j][k]);
                                if(max<array[j][k]){
                                        
                                        k=0;
                                        max = array[j][k];

                                        //交換
                                        for(s=0;s<3;s++){

                                                tmp = array[j][s];
                                                array[j][s] = array[i][s];
                                                array[i][s] = tmp;

                                        }
                                        
                                        /*
                                        //確認出力
                                        System.out.println("----------------------");
                                        for(s=0;s<count;s++){

                                                for(t=0;t<3;t++){

                                                        System.out.print(array[s][t] + " ");
                                                }

                                                System.out.println("");
                                        }
                                        System.out.println("----------------------");
                                        */

                                }else if(max==array[j][k]){

                                        //k++;
                                        //max = array[i][k];
                                        //j--;
                                        if(k==2){
                                                k=0;
                                                //交換
                                                for(s=0;s<3;s++){
                                                    
                                                        tmp = array[i+1][s];
                                                        array[i+1][s] = array[j][s];
                                                        array[j][s] = tmp; 

                                                }
                                                /*
                                                //確認出力
                                                System.out.println("----------------------");
                                                for(s=0;s<count;s++){

                                                        for(t=0;t<3;t++){

                                                                System.out.print(array[s][t] + " ");
                                                        }

                                                        System.out.println("");
                                                }
                                                System.out.println("----------------------");
                                                */
                                                i++;

                                        }else{

                                                k++;
                                                max = array[i][k];
                                                j--;
                                        }

                                }else{

                                        k=0;
                                        max = array[i][k];
                                }


                        }

                }

                //確認出力
                System.out.println("----------------------");
                for(s=0;s<count;s++){

                        for(t=0;t<3;t++){

                                System.out.print(array[s][t]);

                                if(t!=2){
                                        System.out.print(" ");

                                }else{

                                }
                        }
                        System.out.println("");
                }
                //System.out.println("----------------------");

        }
}

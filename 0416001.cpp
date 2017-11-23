#include <iostream>
#include <fstream>
#include <cstdlib>
#include <pthread.h>
#include <memory.h>
#include <string.h>
#include <semaphore.h>
#include <vector>
#include <algorithm>
#include <sys/time.h>

using namespace std;
sem_t  sem_T0 , sem_T1 , sem_T2 , sem_T3 , sem_T4 , sem_T5 , sem_T6 , sem_T7 ,sem_T8 , sem_T9 , sem_T10 , sem_T11 , sem_T12 , sem_T13 , sem_T14 , sem_T15 ,sem_bottom[8] , sem_all_tasks;//set up all semaphore
unsigned long long int total_num;//number of element
vector<long long int> array;//vector for MT
vector<long long int> array_st;//vector for ST
vector<long long int>ar2,  ar3 ,ar4 , ar5 , ar6 ,ar7 ,ar8 , ar9 , ar10 ,ar11 ,ar12 ,ar13 ,ar14 , ar15;
struct timeval start_MT  , end_MT , start_ST , end_ST;


void * wait_bottom(void * tmp)/*T0 thread work here and print here*/
{
  int i = 0;
  for(; i <8 ;i++)
  sem_wait(&sem_bottom[i]);//wait bottom level finish all tasks

  gettimeofday(&end_MT , 0);
  double sec = end_MT.tv_sec - start_MT.tv_sec;
  double msec = end_MT.tv_usec - start_MT.tv_usec;
  cout<<"multi-thread"<<endl;
  cout<<"elased "<<1000*sec+msec/1000<<" ms\n";

  gettimeofday(&start_ST , 0);

  for(unsigned long long int k=0; k<array_st.size(); k++)
    for(unsigned long long int u=0;u<array_st.size()-1;u++ )
    {
      if(array_st[u]>array_st[u+1])
      {
        swap(array_st[u+1] , array_st[u]);
      }
    }

  gettimeofday(&end_ST , 0);
  double sec1 = end_ST.tv_sec - start_ST.tv_sec;
  double msec1 = end_ST.tv_usec - start_ST.tv_usec;

  cout<<"single thread"<<endl;
  cout<<"elased "<<1000*sec1+msec1/1000<<" ms\n";

  for(; i>=0 ;i--)
  sem_destroy(&sem_bottom[i]);//destroy all semaphore
  sem_post(&sem_all_tasks);
  pthread_exit(NULL);//T0 end here
}

void *partition1(void * tmp)/*T1 thread partition the array here*/
{
  sem_wait(&sem_T1);
  gettimeofday(&start_MT , 0);

  long long int left = 0 , right = array.size() ;
  long long int pivot = array[left];
  for(unsigned long long int i =left ; i<right ; i++)
  {
    if(array[i]>pivot)
      ar3.push_back(array[i]);
    else
      ar2.push_back(array[i]);
  }

  sem_post(&sem_T2);
  sem_post(&sem_T3);
  sem_destroy(&sem_T1);
  pthread_exit(NULL);

}
void *partition2(void * tmp)//T2 thread partition the array here
{
  sem_wait(&sem_T2);

  long long int left = 0 , right = ar2.size();
  if(ar2.size()==0)
  {
    sem_post(&sem_T4);
    sem_post(&sem_T5);
    sem_destroy(&sem_T2);
    pthread_exit(NULL);
  }
  long long  int pivot = ar2[left];

  for(unsigned long long int i=left; i<right ; i++)
  {
   
    if(ar2[i]>pivot)
      ar5.push_back(ar2[i]);
    else 
      ar4.push_back(ar2[i]);

  }

  sem_post(&sem_T4);
  sem_post(&sem_T5);
  sem_destroy(&sem_T2);
  pthread_exit(NULL);

}
void *partition3(void * tmp)//T3 thread partition the array here
{
  sem_wait(&sem_T3);
  long long int left = 0 , right = ar3.size() ;
  if(ar3.size()==0)
  {
    sem_post(&sem_T6);
    sem_post(&sem_T7);
    sem_destroy(&sem_T3);
    pthread_exit(NULL);
  }
  long long int pivot = ar3[left];

  for(unsigned long long int i =left ; i<right ; i++)
  {
    if(ar3[i]>pivot)
      ar7.push_back(ar3[i]);
    else
      ar6.push_back(ar3[i]);
  }


  sem_post(&sem_T6);
  sem_post(&sem_T7);
  sem_destroy(&sem_T3);
  pthread_exit(NULL);

}
void *partition4(void * tmp)//T4 thread partition the array here
{
  sem_wait(&sem_T4);

  long long int left = 0 , right = ar4.size();
    if(ar4.size()==0)
  {
    sem_post(&sem_T8);
    sem_post(&sem_T9);
    sem_destroy(&sem_T4);
    pthread_exit(NULL);
  }
  long long  int pivot = ar4[left];

  for(unsigned long long int i =left ; i<right ; i++)
  {
    if(ar4[i]>pivot)
      ar9.push_back(ar4[i]);
    else
      ar8.push_back(ar4[i]);
  }


  sem_post(&sem_T8);
  sem_post(&sem_T9);
  sem_destroy(&sem_T4);
  pthread_exit(NULL);

}
void *partition5(void * tmp)//T5 thread partition the array here
{
  sem_wait(&sem_T5);

  long long int left = 0 , right = ar5.size();
  if(ar5.size()==0)
  {
    sem_post(&sem_T10);
    sem_post(&sem_T11);
    sem_destroy(&sem_T5);
    pthread_exit(NULL);
  }
  long long int pivot = ar5[left];

  for(unsigned long long int i =left ; i<right ; i++)
  {
    if(ar5[i]>pivot)
      ar11.push_back(ar5[i]);
    else
      ar10.push_back(ar5[i]);
  }

  sem_post(&sem_T10);
  sem_post(&sem_T11);
  sem_destroy(&sem_T5);
  pthread_exit(NULL);

}
void *partition6(void * tmp)//T6 thread partition the array here
{
  sem_wait(&sem_T6);

  long long int left = 0 , right = ar6.size();
  if(ar6.size()==0)
  {
    sem_post(&sem_T12);
    sem_post(&sem_T13);
    sem_destroy(&sem_T6);
    pthread_exit(NULL);
  }
  long long int pivot = ar6[left];
  for(unsigned long long int i =left ; i<right ; i++)
  {
    if(ar6[i]>pivot)
      ar13.push_back(ar6[i]);
    else
      ar12.push_back(ar6[i]);
  }


  sem_post(&sem_T12);
  sem_post(&sem_T13);
  sem_destroy(&sem_T6);
  pthread_exit(NULL);

}
void *partition7(void * tmp)//T7 thread partition the array here
{
  sem_wait(&sem_T7);

  long long int left = 0 , right = ar7.size();
  if(ar7.size()==0)
  {
    sem_post(&sem_T14);
    sem_post(&sem_T15);
    sem_destroy(&sem_T7);
    pthread_exit(NULL);
  }
  long long int pivot = ar7[left];
  for(unsigned long long int i =left ; i<right ; i++)
  {
    if(ar7[i]>pivot)
      ar15.push_back(ar7[i]);
    else
      ar14.push_back(ar7[i]);
  }

  sem_post(&sem_T14);
  sem_post(&sem_T15);
  sem_destroy(&sem_T7);
  pthread_exit(NULL);

}
void *sort8(void * tmp)//T8 thread bubble sort
{

  sem_wait(&sem_T8);

  if(ar8.size()==0)
  {

    sem_post(&sem_bottom[0]);
    pthread_exit(NULL);
  }

  for(unsigned long long int i =0 ; i<ar8.size(); i++)
      for(unsigned long long int j =0 ; j<ar8.size()-1; j++)
      {
        if(ar8[j]>ar8[j+1])
          swap(ar8[j] , ar8[j+1]);
      }

  sem_post(&sem_bottom[0]);
  pthread_exit(NULL);

}
void *sort9(void * tmp)//T9 thread bubble sort
{
  sem_wait(&sem_T9);
  
   if(ar9.size()==0)
  {
    sem_post(&sem_bottom[1]);
    pthread_exit(NULL);
  }
  /*bubble sort here */
  for(unsigned long long int i =0 ; i<ar9.size(); i++)
      for(unsigned long long int j =0 ; j<ar9.size()-1; j++)
      {
        if(ar9[j]>ar9[j+1])
          swap(ar9[j] , ar9[j+1]);
      }

  sem_post(&sem_bottom[1]);
  pthread_exit(NULL);

}
void *sort10(void * tmp)//T10 thread bubble sort
{
  sem_wait(&sem_T10);

  if(ar10.size()==0)
  {
    sem_post(&sem_bottom[2]);
    pthread_exit(NULL);
  }
  /*bubble sort here */
  for(unsigned long long int i =0 ; i<ar10.size(); i++)
      for(unsigned long long int j =0 ; j<ar10.size()-1; j++)
      {
        if(ar10[j]>ar10[j+1])
          swap(ar10[j] , ar10[j+1]);
      }

  sem_post(&sem_bottom[2]);
  pthread_exit(NULL);

}
void *sort11(void * tmp)//T11 thread bubble sort
{
  sem_wait(&sem_T11);

 if(ar11.size()==0)
  {
    sem_post(&sem_bottom[3]);
    pthread_exit(NULL);
  }
  /*bubble sort here */
  for(unsigned long long int i =0 ; i<ar11.size(); i++)
      for(unsigned long long int j =0 ; j<ar11.size()-1; j++)
      {
        if(ar11[j]>ar11[j+1])
          swap(ar11[j] , ar11[j+1]);
      }

  sem_post(&sem_bottom[3]);
  pthread_exit(NULL);//exit

}
void *sort12(void * tmp)//T12 thread bubble sort
{
  sem_wait(&sem_T12);//wait T6 to signal it

  if(ar12.size()==0)
  {
    sem_post(&sem_bottom[4]);
    pthread_exit(NULL);
  }
  /*bubble sort here */
  for(unsigned long long int i =0 ; i<ar12.size(); i++)
      for(unsigned long long int j =0 ; j<ar12.size()-1; j++)
      {
        if(ar12[j]>ar12[j+1])
          swap(ar12[j] , ar12[j+1]);
      }

  sem_post(&sem_bottom[4]);
  pthread_exit(NULL);//exit

}
void *sort13(void * tmp)//T13 thread bubble sort
{
  sem_wait(&sem_T13);//wait T6 to signal it


  if(ar13.size()==0)
  {
    sem_post(&sem_bottom[5]);
    pthread_exit(NULL);
  }
  /*bubble sort here */
  for(unsigned long long int i =0 ; i<ar13.size(); i++)
      for(unsigned long long int j =0 ; j<ar13.size()-1; j++)
      {
        if(ar13[j]>ar13[j+1])
          swap(ar13[j] , ar13[j+1]);
      }

  sem_post(&sem_bottom[5]);
  pthread_exit(NULL);//exit

}
void *sort14(void * tmp)//T14 thread bubble sort
{
  sem_wait(&sem_T14);//wait T7 to signal it 

  if(ar14.size()==0)
  {
    sem_post(&sem_bottom[6]);
    pthread_exit(NULL);
  }
  /*bubble sort here */
  for(unsigned long long int i =0 ; i<ar14.size(); i++)
      for(unsigned long long int j =0 ; j<ar14.size()-1; j++)
      {
        if(ar14[j]>ar14[j+1])
          swap(ar14[j] , ar14[j+1]);
      }

  sem_post(&sem_bottom[6]);

  pthread_exit(NULL);//exit

}
void *sort15(void * tmp)//T15 thread bubble sort
{
  sem_wait(&sem_T15);//wait T7 to signal it

  if(ar15.size()==0)
  {
    sem_post(&sem_bottom[7]);
    pthread_exit(NULL);
  }
  /*bubble sort here */
  for(unsigned long long int i =0 ; i<ar15.size(); i++)
      for(unsigned long long int j =0 ; j<ar15.size()-1; j++)
      {
        if(ar15[j]>ar15[j+1])
          swap(ar15[j] , ar15[j+1]);
      }

  sem_post(&sem_bottom[7]);
  pthread_exit(NULL);//exit

}
int main()
{
  /*create semaphore */
  sem_init(&sem_all_tasks , 0 , 0);//At T0 to wait for all tasks be done
  sem_init(&sem_T0 , 0 , 0);
  sem_init(&sem_T1 , 0 , 0);
  sem_init(&sem_T2 , 0 , 0);
  sem_init(&sem_T3 , 0 , 0);
  sem_init(&sem_T4 , 0 , 0);
  sem_init(&sem_T5 , 0 , 0);
  sem_init(&sem_T6 , 0 , 0);
  sem_init(&sem_T7 , 0 , 0);
  sem_init(&sem_T8 , 0 , 0);
  sem_init(&sem_T9 , 0 , 0);
  sem_init(&sem_T10 , 0 , 0);
  sem_init(&sem_T11 , 0 , 0);
  sem_init(&sem_T12 , 0 , 0);
  sem_init(&sem_T13 , 0 , 0);
  sem_init(&sem_T14 , 0 , 0);
  sem_init(&sem_T15 , 0 , 0);
  int i = 0;
  for(; i<8 ; i++)
    sem_init(&sem_bottom[i] , 0 , 0);
  
  /*input the file name*/
  string name;
  //cout<<"Please enter the input file name\n>";
  cin>>name ;

  ifstream fp;
  unsigned long long int num;
  //fp.open("input_test.txt" , std::ifstream::in);
  fp.open((const char *)name.c_str() , std::ifstream::in);

  fp>>num;
  total_num=num;
  long long int  x;


  unsigned long long int length_tmp = 0;
  for(; length_tmp < num ; length_tmp++)
  {

    fp>>x;
    array.push_back(x);
    array_st.push_back(x);

  }
  void * tmp;
  /*create all threads at the begining*/
  pthread_t t0 , t1 ,t2 ,t3 ,t4, t5 , t6 , t7 , t8 , t9 ,t10 ,t11 ,t12 ,t13 ,t14 , t15 ;
  pthread_create(&t0 , NULL , wait_bottom ,tmp );
  pthread_create(&t1 , NULL , partition1 , tmp);
  pthread_create(&t2 , NULL , partition2 , tmp);
  pthread_create(&t3 , NULL , partition3 , tmp);
  pthread_create(&t4 , NULL , partition4 , tmp);
  pthread_create(&t5 , NULL , partition5 , tmp);
  pthread_create(&t6 , NULL , partition6 , tmp);
  pthread_create(&t7 , NULL , partition7 , tmp);
  pthread_create(&t8 , NULL , sort8 , tmp);
  pthread_create(&t9 , NULL , sort9 , tmp);
  pthread_create(&t10 , NULL , sort10 , tmp);
  pthread_create(&t11 , NULL , sort11 , tmp);
  pthread_create(&t12 , NULL , sort12 , tmp);
  pthread_create(&t13 , NULL , sort13 , tmp);
  pthread_create(&t14 , NULL , sort14 , tmp);
  pthread_create(&t15 , NULL , sort15 , tmp);

  sem_post(&sem_T1);//call T1 to work 
  sem_wait(&sem_all_tasks);//wait for every thread finish their work

  fp.close();
  
  /* MT output here*/
  fstream fout1("output1.txt" , std::ofstream::out);
  for(unsigned long long int i =0 ; i<ar8.size() ;i++)
    fout1<<ar8[i]<<" ";
  for(unsigned long long int i =0 ; i<ar9.size() ;i++)
    fout1<<ar9[i]<<" ";
  for(unsigned long long int i =0 ; i<ar10.size() ;i++)
    fout1<<ar10[i]<<" ";
  for(unsigned long long int i =0 ; i<ar11.size() ;i++)
    fout1<<ar11[i]<<" ";
  for(unsigned long long int i =0 ; i<ar12.size() ;i++)
    fout1<<ar12[i]<<" ";
  for(unsigned long long int i =0 ; i<ar13.size() ;i++)
    fout1<<ar13[i]<<" ";
  for(unsigned long long int i =0 ; i<ar14.size() ;i++)
    fout1<<ar14[i]<<" ";
  for(unsigned long long int i =0 ; i<ar15.size() ;i++)
    fout1<<ar15[i]<<" ";
  fout1<<endl;
  fout1.close();
  
  /*ST output here*/
  fstream fout2("output2.txt" , std::ofstream::out);
  for(unsigned long long int i=0 ; i<num ;i++)
    fout2<<array_st[i]<<" ";
  fout2<<endl;
  fout2.close();


}

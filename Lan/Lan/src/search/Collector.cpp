//#include "Collector.h"
//
//Collector::Collector()
//{
//	count=0;
//}
//void Collector::collect(DocScorePair p)
//{
//	queue.push_back(p);
//}
//bool Collector::hasNext()
//{
//	if(count<queue.size())
//	{
//		return true;
//	}
//	return false;
//}
//DocScorePair Collector::getDocScorePair()
//{
//	DocScorePair docpair=queue[count];
//	count++;
//	return  docpair;
//}
//
//void Collector::quick_sort(int l,int r)  //int s[], int l, int r
//{
//    if (l < r)
//    {
//        //Swap(s[l], s[(l + r) / 2]); //���м��������͵�һ�������� �μ�ע1
//        int i = l, j = r;
//		double x=queue[l].getScore();
//		DocScorePair docpair=queue[l];
//        while (i < j)
//        {
//			while(i < j && queue[j].getScore() <= x) // ���������ҵ�һ��С��x����
//                j--;  
//            if(i < j) 
//				queue[i++] = queue[j];
//			while(i < j && queue[i].getScore() > x) // ���������ҵ�һ�����ڵ���x����
//				i++;  
//			if(i < j) 
//				queue[j--] = queue[i];
//        }
//        queue[i] = docpair;
//        quick_sort(l, i - 1); // �ݹ���� 
//        quick_sort(i + 1, r);
//    }
//}
//
//void Collector::sort()
//{
//	int numofqueue=(int)queue.size();
//	quick_sort(0,numofqueue-1);
//
//}
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
//        //Swap(s[l], s[(l + r) / 2]); //将中间的这个数和第一个数交换 参见注1
//        int i = l, j = r;
//		double x=queue[l].getScore();
//		DocScorePair docpair=queue[l];
//        while (i < j)
//        {
//			while(i < j && queue[j].getScore() <= x) // 从右向左找第一个小于x的数
//                j--;  
//            if(i < j) 
//				queue[i++] = queue[j];
//			while(i < j && queue[i].getScore() > x) // 从左向右找第一个大于等于x的数
//				i++;  
//			if(i < j) 
//				queue[j--] = queue[i];
//        }
//        queue[i] = docpair;
//        quick_sort(l, i - 1); // 递归调用 
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
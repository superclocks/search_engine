#include "Analyzers.h"
#include "Directory.h"
#include "Document.h"
#include "IndexReader.h"
#include "Collector.h"
#include "DocScorePair.h"
#include "IndexSearcher.h"
#include "Query.h"
#include "QueryParser.h"
#include "IndexWriter.h"
#include "Field.h"
#include "StandardAnalyzer.h"

#include <iostream>
using namespace std;

int main(int argv,char** argc)
{
	//Lan::analysis::standard::StandardAnalyzer an;
	Lan::analysis::SimpleAnalyzer an;
	IndexWriter* writer=new IndexWriter("sdfsf",&an,false);
	Document* doc = new Document();
	Field* field = new Field("path","c:\\ada",Field::Store_Yes|Field::Index_UnTokenized);
	doc->add(*field);
	field = new Field("content","asfa sfasf ssddf fdf",Field::Store_Yes|Field::Index_UnTokenized);
	doc->add(*field);

	writer->addDocument(doc);
	return 0;
}

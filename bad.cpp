#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include <cmath>

using namespace std;
const int MAX_RESULT_DOCUMENT_COUNT = 5;
string ReadLine() {
    string s;
    getline(cin, s);
    return s;
}
int ReadLineWithNumber() {
    int result = 0;
    cin >> result;
    ReadLine();
    return result;
}
vector<string> SplitIntoWords(const string& text) {
    vector<string> words;
    string word;
    for (const char c : text) {
        if (c == ' ') {
            if (!word.empty()) {
                words.push_back(word);
                word.clear();
            }
        } else {
            word += c;
        }
    }
    if (!word.empty()) {
        words.push_back(word);
    }
    return words;
}
struct Document {
    int id;
    double relevance;
};
class SearchServer {
public:
    void SetStopWords(const string& text) {
        for (const string& word : SplitIntoWords(text)) {
            stop_words_.insert(word);
        }
    }
    
    // добавляем новый документ в мапу, высчитывая значения tf 
    void AddDocument(int document_id, const string& document) {
        for (const string& word : SplitIntoWordsNoStop(document)) {
           document_count_++;
           double tf = 1.0/SplitIntoWordsNoStop(document).size() * count(SplitIntoWordsNoStop(document).begin(), SplitIntoWordsNoStop(document).end(), word);
            
   
         
            
            word_to_documents_[word].insert({document_id, tf});
        }
        
       
    }
   
    vector<Document> FindTopDocuments(const string& raw_query) const {
        const Query query = ParseQuery(raw_query);
        auto matched_documents = FindAllDocuments(query);
       sort(matched_documents.begin(), matched_documents.end(), // отсортируем по релевантности
             [](const Document& lhs, const Document& rhs) {
                 return lhs.relevance > rhs.relevance;
             });
        if (matched_documents.size() > MAX_RESULT_DOCUMENT_COUNT) {
            matched_documents.resize(MAX_RESULT_DOCUMENT_COUNT);
        } 
        return matched_documents;
    }
private:
    int document_count_ = 0;    
    struct QueryWord {
        string data;
        bool is_minus;
        bool is_stop;
    };
    struct Query {
        set<string> plus_words;
        set<string> minus_words;
    };
    set<string> stop_words_;
    
    // будем хранить в словаре номер документа сразу с TF
 
    map<string, map<int, double>> word_to_documents_;
    
    bool IsStopWord(const string& word) const {
        return stop_words_.count(word) > 0;
    }
    
    vector<string> SplitIntoWordsNoStop(const string& text) const {
        vector<string> words;
        for (const string& word : SplitIntoWords(text)) {
            if (!IsStopWord(word)) {
                words.push_back(word);
            }
        }
        return words;
    }
    
    QueryWord ParseQueryWord(string text) const {
        bool is_minus = false;
        // Word shouldn't be empty
        if (text[0] == '-') {
            is_minus = true;
            text = text.substr(1);
        }
        return {text, is_minus, IsStopWord(text)};
    }
    
    Query ParseQuery(const string& text) const {
        Query query;
        for (const string& word : SplitIntoWords(text)) {
            const QueryWord query_word = ParseQueryWord(word);
            if (!query_word.is_stop) {
                if (query_word.is_minus) {
                    query.minus_words.insert(query_word.data);
                } else {
                    query.plus_words.insert(query_word.data);
                }
            }
        }
        return query;
    }
    
    vector<Document> FindAllDocuments(const Query& query) const {
        map<int, double> document_to_relevance;
        // проходим по плюс-словам
        for (const string& word : query.plus_words) {
            if (word_to_documents_.count(word) == 0) {
                continue;
            }
            
          // Если слово есть в словаре
            // вычилим релевантнось
            double idf = log (document_count_ / word_to_documents_.at(word).size());
            for (auto &[id, tf] : word_to_documents_.at(word)) {            
                double current_relevance = idf * tf;
                
                // запишим результат в словарь id-релевантось сумируя с прошлыми записями по id
                //для этого проверим если запись для этого id если нет то создадим
                if (document_to_relevance.count(id) == 0) {
                   document_to_relevance.insert({id, current_relevance}); 
                }
                // если есть то увеличим релевантнось
                else {document_to_relevance[id] += current_relevance; }
                
                }
        }
        
            
            // проходим по минус словам
        for (const string& word : query.minus_words) {
            if (word_to_documents_.count(word) == 0) {
                continue;
            }
            for (auto &[id, tf] : word_to_documents_.at(word)) {               
                     if (!document_to_relevance.count(id) == 0) {
                         document_to_relevance.erase(id);
                     } 
                 
                
                
            }
        }
        
        vector<Document> matched_documents;
        for (const auto &[document_id, relevance] : document_to_relevance) {
            matched_documents.push_back({document_id, relevance});
        }
        
        return matched_documents;
    }
};
SearchServer CreateSearchServer() {
    SearchServer search_server;
    search_server.SetStopWords(ReadLine());
    const int document_count = ReadLineWithNumber();
    for (int document_id = 0; document_id < document_count; ++document_id) {
        search_server.AddDocument(document_id, ReadLine());
    }
    return search_server;
}
int main() {
    const SearchServer search_server = CreateSearchServer();
    const string query = ReadLine();
    for (const auto& [document_id, relevance] : search_server.FindTopDocuments(query)) {
        cout << "{ document_id = "s << document_id << ", "
             << "relevance = "s << relevance << " }"s << endl;
    }

}
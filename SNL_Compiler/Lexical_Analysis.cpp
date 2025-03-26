#include "main.h"

//��ӡ������
void printwrong() {
	cout << "����ĳ�����дʷ�����" << endl;
}

//��ӡ�﷨���Ŀո�
void printq(int size3, ofstream& outputFile) {
	for (int w = 0; w < distant * size3; w++) {
		cout << " ";
		outputFile << " ";
	}
}

//��ӡtoken���е�����̨
void printtoken(ofstream& outputFile, vector<Token>token) {
	cout << "\n\n���򾭹��ʷ�������֮���Token����Ϊ:" << endl;
	for (int i = 0; i < size1 - 1; i++) {
		cout << token[i].value1 << "," << token[i].value2 << endl;
		outputFile << token[i].value1 << "," << token[i].value2 << endl;
	}
	cout << token[size1 - 1].value1 << "," << token[size1 - 1].value2 << endl << "EOF";
	outputFile << token[size1 - 1].value1 << "," << token[size1 - 1].value2 << endl << "EOF";
}

//ͨ��һ�������ַ���,����token����,�ʷ��������ĺ��ĳ���
void generatetoken(string input, int len) {
	int i = 0;
	while (i < len) {
		//�������'\n'�Ϳո�
		if (input[i] == ' ' || input[i] == '\n') {
			i = i + 1;
			continue;
		}
		//�����������
		if (input[i] >= '0' && input[i] <= '9') {
			string tmp = "";
			tmp += input[i];
			int j = i + 1;
			while (j < len) {
				if (input[j] >= '0' && input[j] <= '9') {
					tmp += input[j];
					j++;
				}
				else {
					i = j;
					break;
				}
			}
			//����Ҫ�ж�������ѧ�±껹�����֣�����ط����±��Ѿ���i+1�ˣ����Բ����ٱ�
			if (i >= len) {
				Token token1;
				token1.value1 = "NUM";
				token1.value2 = tmp;
				size1 = size1 + 1;
				token.push_back(token1);
			}
			else {
				//�������ұ���]�����ж������������͵��±�
				if (input[i] == ']') {
					Token token1;
					token1.value1 = "UNDERANGE";
					token1.value2 = tmp;
					size1 = size1 + 1;
					token.push_back(token1);
				}
				else {
					Token token1;
					token1.value1 = "NUM";
					token1.value2 = tmp;
					size1 = size1 + 1;
					token.push_back(token1);
				}
			}
			continue;
		}
		//��������ַ�
		if ((input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z')) {
			string tmp = "";
			tmp += input[i];
			int j = i + 1;
			while (j < len) {
				if ((input[j] >= 'a' && input[j] <= 'z') || (input[j] >= 'A' && input[j] <= 'Z') || (input[j] >= '0' && input[j] <= '9')) {
					tmp += input[j];
					j = j + 1;
				}
				else {
					i = j;
					break;
				}
			}
			//cout << "\n" << "******" << tmp << endl;
			if (tmp.length() == 1) {    //�����char���͵�
				Token token1;
				token1.value1 = "CHAR";
				token1.value2 = tmp;
				size1 = size1 + 1;
				token.push_back(token1);
			}
			else {
				//�ж������Ǳ�����
				bool flag2 = false;
				for (int k = 0; k < 21; k++) {
					if (tmp == reservedWords[k]) {
						Token token1;
						token1.value1 = "reserved word";
						token1.value2 = reservedWords1[k]; //���ｫ�����ֵ�Сдת��ɴ�д
						size1 = size1 + 1;
						token.push_back(token1);
						flag2 = true;
						break;
					}
				}
				//�����������ͨ�ַ���
				if (!flag2) {
					Token token1;
					token1.value1 = "ID";
					token1.value2 = tmp;
					size1 = size1 + 1;
					token.push_back(token1);
				}

			}
			continue;
		}
		//���������ע�ͺͳ�����
		if (input[i] == '{') {
			int j = i; //ͨ��˫ָ���ҵ���һ��}
			bool flag = false; //��ʶ�Ƿ��ҵ���}
			while (j < len) {
				if (input[j] == '}') {
					i = j + 1;
					flag = true;
					break;
				}
				j = j + 1;
			}
			if (!flag) {
				printwrong();
			}
			continue;
		}
		//���������ע��,������
		if (input[i] == '}') {
			i = i + 1;
			continue;
		}
		//����������ֽ��+
		if (input[i] == '+') {
			Token token1;
			token1.value1 = SingleDelimiter[0];
			token1.value2 = '+';
			size1 = size1 + 1;
			token.push_back(token1);
			i = i + 1;
			continue;
		}
		//����������ֽ��-
		if (input[i] == '-') {
			Token token1;
			token1.value1 = SingleDelimiter[1];
			token1.value2 = '-';
			size1 = size1 + 1;
			token.push_back(token1);
			i = i + 1;
			continue;
		}
		//����������ֽ��*
		if (input[i] == '*') {
			Token token1;
			token1.value1 = SingleDelimiter[2];
			token1.value2 = '*';
			size1 = size1 + 1;
			token.push_back(token1);
			i = i + 1;
			continue;
		}
		//����������ֽ��/
		if (input[i] == '/') {
			Token token1;
			token1.value1 = SingleDelimiter[3];
			token1.value2 = '/';
			size1 = size1 + 1;
			token.push_back(token1);
			i = i + 1;
			continue;
		}
		//����������ֽ��(
		if (input[i] == '(') {
			Token token1;
			token1.value1 = SingleDelimiter[4];
			token1.value2 = '(';
			size1 = size1 + 1;
			token.push_back(token1);
			i = i + 1;
			continue;
		}
		//����������ֽ��)
		if (input[i] == ')') {
			Token token1;
			token1.value1 = SingleDelimiter[5];
			token1.value2 = ')';
			size1 = size1 + 1;
			token.push_back(token1);
			i = i + 1;
			continue;
		}
		//����������ֽ��[
		if (input[i] == '[') {
			Token token1;
			token1.value1 = SingleDelimiter[6];
			token1.value2 = '[';
			size1 = size1 + 1;
			token.push_back(token1);
			i = i + 1;
			continue;
		}
		//����������ֽ��]
		if (input[i] == ']') {
			Token token1;
			token1.value1 = SingleDelimiter[7];
			token1.value2 = ']';
			size1 = size1 + 1;
			token.push_back(token1);
			i = i + 1;
			continue;
		}
		//����������ֽ��:
		if (input[i] == ';') {
			Token token1;
			token1.value1 = SingleDelimiter[8];
			token1.value2 = ';';
			size1 = size1 + 1;
			token.push_back(token1);
			i = i + 1;
			continue;
		}
		//����������ֽ��.
		if (input[i] == '.') {
			Token token1;
			token1.value1 = SingleDelimiter[9];
			token1.value2 = '.';
			size1 = size1 + 1;
			token.push_back(token1);
			i = i + 1;
			continue;
		}
		//����������ֽ��<
		if (input[i] == '<') {
			Token token1;
			token1.value1 = SingleDelimiter[10];
			token1.value2 = '<';
			size1 = size1 + 1;
			token.push_back(token1);
			i = i + 1;
			continue;
		}
		//����������ֽ��:����ط��ÿ���һ���ǲ���:=
		if (input[i] == ':') {
			int j = i + 1;
			if (j >= len) {
				Token token1;
				token1.value1 = SingleDelimiter[11];
				token1.value2 = ':';
				size1 = size1 + 1;
				token.push_back(token1);
				i = i + 1;
			}
			else {
				if (input[j] == '=') {
					Token token1;
					token1.value1 = SingleDelimiter[14];
					token1.value2 = ":=";
					size1 = size1 + 1;
					token.push_back(token1);
					i = i + 2;
				}
				else {
					Token token1;
					token1.value1 = SingleDelimiter[11];
					token1.value2 = ':';
					size1 = size1 + 1;
					token.push_back(token1);
					i = i + 1;
				}
			}
			continue;
		}
		//����������ֽ��=
		if (input[i] == '=') {
			Token token1;
			token1.value1 = SingleDelimiter[12];
			token1.value2 = '=';
			size1 = size1 + 1;
			token.push_back(token1);
			i = i + 1;
			continue;
		}
		//����������ֽ��'
		if (input[i] == '\'') {
			Token token1;
			token1.value1 = SingleDelimiter[13];
			token1.value2 = '\'';
			size1 = size1 + 1;
			token.push_back(token1);
			i = i + 1;
			continue;
		}
		//����������ֽ��>
		if (input[i] == '>') {
			Token token1;
			token1.value1 = SingleDelimiter[15];
			token1.value2 = '>';
			size1 = size1 + 1;
			token.push_back(token1);
			i = i + 1;
			continue;
		}
		//����������ֽ��"
		if (input[i] == '"') {
			Token token1;
			token1.value1 = SingleDelimiter[16];
			token1.value2 = '"';
			size1 = size1 + 1;
			token.push_back(token1);
			i = i + 1;
			continue;
		}
		//����������ֽ��,
		if (input[i] == ',') {
			Token token1;
			token1.value1 = SingleDelimiter[17];
			token1.value2 = ',';
			size1 = size1 + 1;
			token.push_back(token1);
			i = i + 1;
			continue;
		}
		//printwrong();
		i = i + 1;
	}
}

//ͨ���±꣬ÿ�εõ�һ��token
Token gettoken(int m) {
	return token[m];
}
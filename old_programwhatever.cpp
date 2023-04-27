char input[50];
short int i;

void sort(int*, short int*);
void sort(int*, short int*, short int);
void arr_delete(int*, short int*);
void asize(short int *, short int *);
int* arr_gen(int, short int*);
short int strlenght(char *s);
short int wordcount(char *s);
void lexeme_w(char *s);
void reverse_w(char *s, short int len);
void lexeme_f(char *s);

int main()
{
	do
	{
		cout << "Welcome to Program Whatever version 1.0 exp." << endl << endl
			<< "Enter 1 for number guessing game" << endl
			<< "Enter 2 for matrix drawing" << endl
			<< "Enter 3 for array operations" << endl
			<< "Enter 4 for string operation" << endl
			<< "Enter ""help"" for more information" << endl
			<< "Enter 9 to quit" << endl
			<< endl << "Entering: ";
		cin >> input;
		switch (strlen(input))
		{

		case 1:
		{
			switch (atoi(input))
			{
			case 1:
			{
				cout << "\nGuess the number v.1.0 and constantly updating\n" << endl;
				break;
			}

			case 2:
			{
				cout << "what is this" << endl;
				break;
			}

			case 3:
			{
				short int *a = new short int, *b = new short int;
				int *arr = NULL;
				short int i = 0;
				*a = 0;
				*b = 0;
				cout << endl << "Array operations" << endl;
				for (; atoi(input) != 9;)
				{
					cout << endl << "Enter 1 to sort array upwards" << endl
						<< "Enter 2 to sort array downwards" << endl
						<< "Enter 3 to delete elements" << endl
						<< "Enter 4 to visualise array" << endl;
					if (!(*a) and !(*b))
					{
						cout << "Enter 5 to enter array sizes" << endl;
					}
					else
					{
						cout << "Enter 5 to enter new array sizes" << endl;
					}

					cout << "Enter 6 to generate random array" << endl
						<< "Enter 7 to manually fill the array" << endl
						<< "Enter 9 to return to main menu" << endl
						<< endl << "Entering: ";
					cin >> input;

					switch (strlen(input))
					{
					case 1:
					{
						if (!(*a) and !(*b) and atoi(input) != 5)
						{
							cout << "You must enter array size first" << endl;
							break;
						}

						else if (!i and atoi(input) != 5 and atoi(input) != 6 and atoi(input) != 7)
						{
							cout << "You must generate or fill the array first" << endl;
							break;
						}

						else
						{
							switch (atoi(input))
							{
							case 1:
							{
								sort(arr, a);
								break;
							}

							case 2:
							{
								sort(arr, a, 1);
								break;
							}

							case 3:
							{
								arr_delete(arr, a);
								break;
							}

							case 4:
							{
								for (i = 0; i < *a; i++)
								{
									cout << *(arr + i) << " ";
								}
								cout << endl << endl;
								break;
							}

							case 5:
							{
								asize(a, b);
								break;
							}

							case 6:
							{
								int n = 0;
								cout << "Enter maximum array number: ";
								cin >> n;
								arr = arr_gen(n, a);
								i++;
								cout << endl << "Array generated" << endl;
								break;
							}

							case 7:
							{
								cout << "Enter numbers: ";
								int *arr_t = new int[*a];
								for (i = 0; i < (*a); i++)
								{
									cin >> *(arr_t + i);
								}
								arr = arr_t;
								break;
							}

							case 9:
							{
								delete[] arr;
								break;
							}
							}
						}
						break;
					}

					default:
					{
						cout << "Invalid command" << endl << endl;
					}
					}
				}
				break;
			}

			case 4:
			{
				cout << endl << "String operations" << endl << endl;
				char str[100] = { '\0' };
				for (; atoi(input) != 5;)
				{

					cout << endl << "Enter 1 for length measurements" << endl
						<< "Enter 2 for lexeme writing" << endl
						<< "Enter 3 for reverse writing" << endl
						<< "Enter 4 for finding lexeme in string" << endl
						<< "Enter 5 to return to main menu" << endl;

					if (str[0])
					{
						cout << "Enter 9 to enter new string" << endl
							<< endl << "Entering: ";
					}
					else
					{
						cout << "Enter 9 to enter string" << endl
							<< endl << "Entering: ";
					}

					cin >> input;
					switch (strlen(input))
					{
					case 1:
					{
						if (!str[0] and atoi(input) != 9 and atoi(input) != 5)
						{
							cout << endl << "You must enter string first" << endl;
							break;
						}

						else
						{
							switch (atoi(input))
							{
							case 1:
							{
								cout << endl << "Sentence lenght is " << strlenght(str) << " symbols" << endl
									<< "Word count: " << wordcount(str) << endl;
								break;
							}

							case 2:
							{
								lexeme_w(str);
								break;
							}

							case 3:
							{
								reverse_w(str, strlen(str));
								break;
							}

							case 4:
							{
								lexeme_f(str);
								cout << "In string: " << str << endl << endl;
								break;
							}

							case 5:
							{
								break;
							}

							case 9:
							{
								cout << "Enter string: ";
								cin.ignore();
								cin.getline(str, 100);
								cout << endl;
								break;
							}

							default:
							{
								cout << "Invalid command" << endl << endl;
								break;
							}

							}

						}
						break;
					}

					default:
					{
						cout << "Invalid command" << endl << endl;
						break;
					}
					}

				}
				break;
			}

			case 9:
			{
				i++;
				break;
			}

			default:
			{
				cout << "Invalid command" << endl << endl;
			}
			}
			break;
		}

		case 4:
		{
			if (!strcmp(input, "Help") or !strcmp(input, "help"))
			{
				cout.fill('-');
				cout.width(80);
				cout << "" << endl;
				cout << "Array operations:" << endl << endl
					<< "Sorting: reorders array in ascending or descending order" << endl
					<< "Delete elements - deletes chosen elements from the array" << endl
					<< "Visualise array - outputs all array elements in order" << endl
					<< "Enter sizes - enters number of rows and numbers in a single row(columns)" << endl
					<< "Generate array - fills the array up with random integer numbers" << endl
					<< "Fill the array - allows to fill the array manually" << endl;
				cout.fill('-');
				cout.width(80);
				cout << "" << endl;
				cout << "String operations:" << endl << endl
					<< "Length measurement - measures length and wordcount of current string" << endl
					<< "Lexeme writing - writes lexemes separately" << endl
					<< "Reverse writing - reverses the string" << endl
					<< "Finding lexeme - finds needed lexeme in string" << endl;
				cout.fill('-');
				cout.width(80);
				cout << "" << endl;
				break;
			}
		}

		default:
		{
			cout << "Invalid command" << endl << endl;
			break;
		}

		}

	} while (!i);


}

void sort(int *arr, short int *len)
{
	short int ti;
	int n = 0;

	for (short int i = 0; i < *len; i++)
	{
		n = *(arr + i);
		for (short int i2 = i + 1; i2 < *len; i2++)
		{
			if (n > *(arr + i2))
			{
				n = *(arr + i2);
				ti = i2;
			}
		}
		*(arr + ti) = *(arr + i);
		*(arr + i) = n;
	}
	cout << endl << "Array sorted" << endl;
}

void sort(int *arr, short int *len, short int)
{
	short int ti = 0;
	int n = 0;

	for (short int i = 0; i < *len; i++)
	{
		n = *(arr + i);
		for (short int i2 = i + 1; i2 < *len; i2++)
		{
			if (n < *(arr + i2))
			{
				n = *(arr + i2);
				ti = i2;
			}
		}
		*(arr + ti) = *(arr + i);
		*(arr + i) = n;
	}
	cout << endl << "Array sorted" << endl;
}

void arr_delete(int *arr, short int *len)
{

	short int d = 0;
	short int num[10] = { 0 };
	int n = 0;

	for (;;)
	{
		char a[10] = { '\0' };
		char *ap = a;
		char c[] = { '0','1','2','3','4','5','6','7','8','9' };
		char *cp = c;

		cout << endl << "Enter a number to delete" << endl
			<< "Enter empty string to quit" << endl
			<< ": ";
		cin.ignore();
		cin.getline(a, 10);

		if (!a[0])
		{
			return;
		}

		for (short int i = 0; i < 10; i++)
		{
			for (short int j = 0; j < 10; j++)
			{
				if (*(ap + i) == *(cp + j))
				{
					num[d] = j;
					d++;
					break;
				}
			}
		}

		if (!d)
		{
			cout << "Invalid number" << endl;
			continue;
		}

		break;
	}

	for (short int i = 0; i < d; i++)
	{
		n += num[i] * pow(10, d - i - 1);
	}

	short int *del = new short int[*len];
	short int j = 0;

	for (short int i = 0; i < *len; i++)
	{
		if (*(arr + i) == n)
		{
			*(del + j) = i;
			j++;
		}
	}

	if (!j)
	{
		cout << "Number not found" << endl;
		return;
	}

	for (short int i = j - 1; i > -1; i--)
	{
		for (short int ii = *(del + i); ii < *len - 1; ii++)
		{
			*(arr + ii) = *(arr + ii + 1);
		}
		(*len)--;
	}

	delete[] del;
	cout << "Operation completed" << endl
		<< "Current array lenght: " << *len << endl;
}

void asize(short int *a, short int *b)
{
	char bs[20] = { '\0' };
	char as[20] = { '\0' };
	for (;;)
	{
		cout << endl << "Number of rows: ";
		cin >> bs;
		switch (strlen(bs))
		{
		case 1:
		case 2:
		case 3:
		{
			if (atoi(bs) > 0)
			{
				break;
			}
		}

		default:
		{
			cout << endl << "Invalid size" << endl;
			continue;
		}

		}

		break;
	}

	for (;;)
	{
		cout << endl << "Numbers in a row: ";
		cin >> as;
		switch (strlen(as))
		{

		case 1:
		case 2:
		case 3:
		{
			if (atoi(as) > 0)
			{
				break;
			}
		}

		default:
		{
			cout << endl << "Invalid size" << endl;
			continue;
		}

		}

		break;
	}

	*a = atoi(as);
	*b = atoi(bs);
}

int* arr_gen(int n, short int *a)
{
	int *arr_t = new int[*a];
	for (short int i = 0; i < (*a); i++)
	{
		*(arr_t + i) = rand() % (n + 1);
	}

	return arr_t;
}

short int strlenght(char *s)
{
	short int len = 0;
	for (; *s; s++, len++);
	return len;
}

short int wordcount(char *s)
{
	short int wc = 0;
	while (*s)
	{
		while (*s and *s != ' ')
		{
			for (; *s and *s != ' '; s++);
			wc++;
		}

		for (; *s == ' '; s++);
	}
	return wc;
}

void lexeme_w(char *s)
{
	while (*s)
	{
		char l[50] = { '\0' }, *lp = l;
		for (; *s and *s != ' '; s++, lp++)
		{
			*lp = *s;
		}
		cout << l << endl;

		for (; *s == ' '; s++);
	}
}

void reverse_w(char *s, short int len)
{
	s += len;
	for (; len >= 0; len--, s--)
	{
		cout << *s;
	}
}

void lexeme_f(char *s)
{
	char lex[30] = { '\0' }, *l = lex;
	short int count = 0;
	cin.ignore();
	for (;;)
	{
		cout << "Write the needed lexeme: ";
		cin.getline(lex, 30);
		if (!*l)
		{
			cout << endl << "You entered empty lexeme" << endl;
			continue;
		}

		for (; *s;)
		{
			for (; *l == *s and *s; s++, l++);
			if (!(*l))
			{
				count++;
			}
			l = lex;
			while (*l != *s and *s)
			{
				s++;
			}
		}

		break;
	}

	cout << endl << "Number of matches: " << count << endl;

}
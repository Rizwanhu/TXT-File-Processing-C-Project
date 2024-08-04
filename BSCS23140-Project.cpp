#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string getword(ifstream &frdr)
{
	string word;
	frdr >> word;
	return word;
}

struct CountryInfo
{
	string country_name;
	string win_probability;
	string bowling_rate_last_10_overs;
	string batting_rate_last_10_overs;
	string batting_rate_middle_overs;
	string best_player;
};

void STAT_OF_COUNTRY(ofstream &outputfile_html, ifstream &frdr, const string &country, CountryInfo &countryInfo)
{

	string sentence;
	string word;
	bool same = false, found = false;
	bool search1 = false, search2 = false, search3 = false, search4 = false, search5 = false;
	int check1 = 0, check2 = 0, check3 = 0, check4 = 0, check5 = 0;

	while (!found)
	{
		while (!frdr.eof())
		{
			getline(frdr, sentence);
			if (sentence == country)
			{
				while (sentence != "")
				{
					if (search1 == false && check1 == 0)
					{
						getline(frdr, sentence);
						for (int i = 0; i < 4; i++)
						{
							word = getword(frdr);
							if (i == 3)
							{
								countryInfo.win_probability = word;
								search1 = true;
								getline(frdr, sentence);
								break;
							}
						}
					}
					else
					{
						getline(frdr, sentence);
					}
					check1++;
					if (check1 == 1)
					{
						frdr.close();
						frdr.open("article.txt");
						break;
					}

					if (check2 == false && check2 == 0)
					{
						getline(frdr, sentence);
						while (sentence != "")
						{
							word = getword(frdr);
							if (word == "bowling")
							{
								word = getword(frdr);
								if (word == "economy")
								{
									word = getword(frdr);
									if (word == "rate")
									{
										word = getword(frdr);
										word = getword(frdr);
										countryInfo.bowling_rate_last_10_overs = word;
										search2 = true;
										break;
									}
								}
							}
							else if (word == "2017." || word == "too." || word == "Warner." || word == "2015.")
								break;
						}
					}
					check2++;
					if (check2 == 1)
					{
						frdr.close();
						frdr.open("article.txt");
						break;
					}

					if (check3 == false && check3 == 0)
					{
						getline(frdr, sentence);
						while (sentence != "")
						{
							word = getword(frdr);
							if (word == "scored")
							{
								word = getword(frdr);
								if (word == "at")
								{
									word = getword(frdr);
									string tempword = word;
									for (int i = 0; i < 7; i++)
									{
										word = getword(frdr);
										if (word == "first")
										{
											word = getword(frdr);
											if (word == "10")
											{
												same = true;
												break;
											}
										}
									}
									if (same == false)
									{
										countryInfo.batting_rate_last_10_overs = tempword;
										search3 = true;
										break;
									}
								}
							}
							else if (word == "2017." || word == "too." || word == "Warner." || word == "2015.")
								break;
						}
					}
					check3++;
					if (check3 == 1)
					{
						frdr.close();
						frdr.open("article.txt");
						break;
					}

					if (check4 == false && check4 == 0)
					{
						getline(frdr, sentence);
						while (sentence != "")
						{
							word = getword(frdr);
							if (word == "batting")
							{
								word = getword(frdr);
								if (word == "rate")
								{
									word = getword(frdr);
									countryInfo.batting_rate_middle_overs = word;
									search4 = true;
									break;
								}
							}
							else if (word == "2017." || word == "too." || word == "Warner." || word == "2015.")
								break;
						}
					}
					check4++;
					if (check4 == 1)
					{
						frdr.close();
						frdr.open("article.txt");
						break;
					}

					if (search5 == false && check5 == 0)
					{
						while (sentence != "" || word != "Crucial")
						{
							getline(frdr, sentence);
							word = getword(frdr);
							if (word == "Crucial")
							{
								word = getword(frdr);
								if (word == "player:")
								{
									word = getword(frdr);
									countryInfo.best_player = word + " " + getword(frdr);
									search5 = true;
									break;
								}
							}
						}
					}
					check5++;
					if (check5 == 1)
					{
						break;
					}
				}
			}
		}
		if (search1 || search2 || search3 || search4 || search5)
		{
			found = true;
		}
		if (found == true)
		{
			if (search1 == false)
				cout << "Probability of winning is not available" << endl;
			if (search2 == false)
				cout << "bowling rate in last 10 over is not available" << endl;
			if (search3 == false)
				cout << "batting rate in last 10 over is not available" << endl;
			if (search4 == false)
				cout << "batting rate in middle over is not available" << endl;
			if (search5 == false)
				cout << "Name of the best player is not available" << endl;
		}
		if (frdr.eof() && found == false)
		{
			frdr.close();
			frdr.open("article.txt");
		}
	}

	cout << "   " << endl;

	outputfile_html << "<tr>\n";
	outputfile_html << "<td>" << (countryInfo.country_name == "" ? "Not Available" : countryInfo.country_name) << "</td>\n";
	outputfile_html << "<td>" << (countryInfo.win_probability == "" ? "Not Available" : countryInfo.win_probability) << "</td>\n";
	outputfile_html << "<td>" << (countryInfo.bowling_rate_last_10_overs == "" ? "Not Available" : countryInfo.bowling_rate_last_10_overs) << "</td>\n";
	outputfile_html << "<td>" << (countryInfo.batting_rate_last_10_overs == "" ? "Not Available" : countryInfo.batting_rate_last_10_overs) << "</td>\n";
	outputfile_html << "<td>" << (countryInfo.batting_rate_middle_overs == "" ? "Not Available" : countryInfo.batting_rate_middle_overs) << "</td>\n";
	outputfile_html << "<td>" << (countryInfo.best_player == "" ? "Not Available" : countryInfo.best_player) << "</td>\n";
	outputfile_html << "</tr>\n";
}

int main()
{

	ifstream frdr("article.txt");
	string country;
	string tempword;
	string nextword;
	string sentence;
	string word;
	bool same = false, found = false;
	bool search1 = false, search2 = false, search3 = false, search4 = false, search5 = false;
	int check1 = 0, check2 = 0, check3 = 0, check4 = 0, check5 = 0;
	cout << "Enetr a valid country" << endl;
	while (!found)
	{
		cin >> country;
		while (!frdr.eof())
		{
			getline(frdr, sentence);
			if (sentence == country)
			{
				while (sentence != "")
				{
					if (search1 == false && check1 == 0)
					{
						getline(frdr, sentence);
						for (int i = 0; i < 4; i++)
						{
							word = getword(frdr);
							if (i == 3)
							{
								cout << "Probability of winning: " << word << endl;
								search1 = true;
								getline(frdr, sentence);
								break;
							}
						}
					}
					else
					{
						getline(frdr, sentence);
					}
					check1++;
					if (check1 == 1)
					{
						frdr.close();
						frdr.open("article.txt");
						break;
					}
					if (check2 == false && check2 == 0)
					{
						getline(frdr, sentence);
						while (sentence != "")
						{
							word = getword(frdr);
							if (word == "bowling")
							{
								word = getword(frdr);
								if (word == "economy")
								{
									word = getword(frdr);
									if (word == "rate")
									{
										word = getword(frdr);
										word = getword(frdr);
										cout << "Bowling rate in last 10 overs: " << word << endl;
										search2 = true;
										break;
									}
								}
							}
							else if (word == "2017." || word == "too." || word == "Warner." || word == "2015.")
								break;
						}
					}
					check2++;
					if (check2 == 1)
					{
						frdr.close();
						frdr.open("article.txt");
						break;
					}
					if (check3 == false && check3 == 0)
					{
						getline(frdr, sentence);
						while (sentence != "")
						{
							word = getword(frdr);
							if (word == "scored")
							{
								word = getword(frdr);
								if (word == "at")
								{
									word = getword(frdr);
									tempword = word;
									for (int i = 0; i < 7; i++)
									{
										word = getword(frdr);
										if (word == "first")
										{
											word = getword(frdr);
											if (word == "10")
											{
												same = true;
												break;
											}
										}
									}
									if (same == false)
									{
										cout << "Batting rate in last ten overs: " << tempword << endl;
										search3 = true;
										break;
									}
								}
							}
							else if (word == "2017." || word == "too." || word == "Warner." || word == "2015.")
								break;
						}
					}
					check3++;
					if (check3 == 1)
					{
						frdr.close();
						frdr.open("article.txt");
						break;
					}
					if (check4 == false && check4 == 0)
					{
						getline(frdr, sentence);
						while (sentence != "")
						{
							word = getword(frdr);
							if (word == "batting")
							{
								word = getword(frdr);
								if (word == "rate")
								{
									word = getword(frdr);
									tempword = word;
									cout << "Batting rate in middle over: " << word << endl;
									search4 = true;
									break;
								}
							}
							else if (word == "2017." || word == "too." || word == "Warner." || word == "2015.")
								break;
						}
					}
					check4++;
					if (check4 == 1)
					{
						frdr.close();
						frdr.open("article.txt");
						break;
					}
					if (search5 == false && check5 == 0)
					{
						while (sentence != "" || word != "Crucial")
						{
							getline(frdr, sentence);
							word = getword(frdr);
							if (word == "Crucial")
							{
								word = getword(frdr);
								if (word == "player:")
								{
									word = getword(frdr);
									cout << "Name of best player: " << word << " ";
									word = getword(frdr);
									cout << word << endl;
									search5 = true;
									break;
								}
							}
						}
					}
					check5++;
					if (check5 == 1)
					{
						break;
					}
				}
			}
		}
		if (search1 || search2 || search3 || search4 || search5)
		{
			found = true;
		}
		if (found == true)
		{
			if (search1 == false)
				cout << "Probability of winning is not available" << endl;
			if (search2 == false)
				cout << "bowling rate in last 10 over is not available" << endl;
			if (search3 == false)
				cout << "batting rate in last 10 over is not available" << endl;
			if (search4 == false)
				cout << "batting rate in middle over is not available" << endl;
			if (search5 == false)
				cout << "Name of best player is not available" << endl;
		}
		if (frdr.eof() && found == false)
		{
			cout << "no detail avaliable for the country" << endl;
			frdr.close();
			frdr.open("article.txt");
		}
	}

	if (!frdr.is_open())
	{
		cerr << "error while opening the file" << endl;
		return 1;
	}

	const int size = 4;
	CountryInfo countries[size];

	string country_names[] = {"Afghanistan", "Australia", "Bangladesh", "England"};

	ofstream outputfile_html("final.html");

	if (!outputfile_html.is_open())
	{
		cerr << "error in opening the HTML file" << endl;
		return 1;
	}

	outputfile_html << "<!DOCTYPE html>\n";
	outputfile_html << "<html>\n";
	outputfile_html << "<head>\n";
	outputfile_html << "</head>\n";
	outputfile_html << "<body>\n";
	outputfile_html << "<h2>Country Information</h2>\n";
	outputfile_html << "<table>\n";
	outputfile_html << "<tr>\n";
	outputfile_html << "<th>Country</th>\n";
	outputfile_html << "<th>Probability of Winning</th>\n";
	outputfile_html << "<th>Bowling Rate (Last 10 Overs)</th>\n";
	outputfile_html << "<th>Batting Rate (Last 10 Overs)</th>\n";
	outputfile_html << "<th>Batting Rate (Middle Overs)</th>\n";
	outputfile_html << "<th>Best Player</th>\n";
	outputfile_html << "</tr>\n";

	for (int i = 0; i < size; i++)
	{
		countries[i].country_name = country_names[i];
		STAT_OF_COUNTRY(outputfile_html, frdr, country_names[i], countries[i]);
	}

	outputfile_html << "</table>\n";
	outputfile_html << "</body>\n";
	outputfile_html << "</html>\n";

	outputfile_html.close();

	cout << "                         **********Above & Below details has been written to final.html*********" << endl;

	frdr.close();

	for (int i = 0; i < size; i++)
	{
		cout << "Country: " << countries[i].country_name << endl;
		cout << "Probability of winning: " << countries[i].win_probability << endl;
		cout << "Bowling rate in last 10 overs: " << countries[i].bowling_rate_last_10_overs << endl;
		cout << "Batting rate in last 10 overs: " << countries[i].batting_rate_last_10_overs << endl;
		cout << "Batting rate in middle overs: " << countries[i].batting_rate_middle_overs << endl;
		cout << "Name of best player: " << countries[i].best_player << endl;
		cout << endl;
	}

	cout << "**********the empty are the one's that are not available and those are declared previously according to the country above before ouput has been written to final.html********";
	return 0;
}

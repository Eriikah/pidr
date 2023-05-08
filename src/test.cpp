// #include "potfunction.hpp"
// #include "correlation.hpp"

// int main()
// {

//     vector<Attribute> list_att = setupNodesAndLinks();
//     Attribute Difficulty = Attribute("Difficulty", "resources/courses.csv", 1);
//     Attribute Rating = Attribute("Rating", "resources/courses.csv", 2);
//     Attribute Popularity = Attribute("Popularity", "resources/Professeurs.csv", 1);
//     Attribute Teaching_ability = Attribute("Teaching Ability", "resources/Professeurs.csv", 2);
//     Attribute Intelligence = Attribute("Intelligence", "resources/Students.csv", 1);
//     Attribute Ranking = Attribute("Ranking", "resources/Students.csv", 2);
//     Attribute Grade = Attribute("Grade", "resources/Registration.csv", 1);
//     Attribute Satisfaction = Attribute("Satisfaction", "resources/Registration.csv", 2);
//     // vector<Element> a = getElements(test1);
//     // for (Element i : a)
//     // {
//     //     cout << i.value << "\n";
//     // }

//     vector<pair<double, double>> coupleXY = getValues(Teaching_ability, Ranking);

//     vector<pair<double, double>> test;

//     test.push_back(make_pair(1, 1));
//     test.push_back(make_pair(1, 1));
//     test.push_back(make_pair(1, 1));
//     test.push_back(make_pair(1, 1));
//     test.push_back(make_pair(1, 1));
//     test.push_back(make_pair(1, 2));
//     test.push_back(make_pair(1, 2));
//     test.push_back(make_pair(1, 3));
//     test.push_back(make_pair(2, 1));
//     test.push_back(make_pair(2, 2));
//     test.push_back(make_pair(2, 2));
//     test.push_back(make_pair(2, 2));
//     test.push_back(make_pair(2, 2));
//     test.push_back(make_pair(2, 3));
//     test.push_back(make_pair(3, 3));
//     test.push_back(make_pair(3, 3));
//     test.push_back(make_pair(3, 3));
//     test.push_back(make_pair(3, 3));
//     test.push_back(make_pair(3, 2));
//     test.push_back(make_pair(3, 1));

//     cout << order(test) << "\n";

//     // vector<Attribute> pot_Intelligence = pot(Intelligence, list_att);
//     // vector<Attribute> pot_Difficulty = pot(Difficulty, list_att);
//     // vector<Attribute> pot_Rating = pot(Rating, list_att);
//     // vector<Attribute> pot_Popularity = pot(Popularity, list_att);
//     // vector<Attribute> pot_Teaching_ability = pot(Teaching_ability, list_att);
//     // vector<Attribute> pot_Ranking = pot(Ranking, list_att);
//     // vector<Attribute> pot_Grade = pot(Grade, list_att);
//     // vector<Attribute> pot_Satisfaction = pot(Satisfaction, list_att);

//     // for (auto att : pot_Difficulty)
//     // {
//     //     cout << att.filename << " : " << att.name << "\n";
//     // }

//     // return 0;
// }

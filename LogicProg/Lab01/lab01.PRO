/*Ильин Андрей 1032201656 НФИбд-01-20*/

/*
Parts of the World:
    Australia / Asia / America / Antarctica / Africa / Europe.
*/

/*country(id, "Name", part_of_world, population)*/
country(0, "Germany", 		europe, 	82175684).
country(1, "France", 			europe, 	66991000).
country(2, "Italy", 				europe, 	60795612).
country(3, "China", 			asia, 		1380083000).
country(4, "India", 			asia, 		1313204000).
country(5, "USA", 				america, 	325850000).
country(6, "Brazil", 			america, 	205737996).
country(7, "Australia",	 	australia, 	24067700).
country(8, "New Zealand", 	australia, 	4596700).
country(9, "Egypt", 			africa, 		88487396).

country(10, "South Africa", africa, 54956900).

/*capital(id, "Name", population)*/
capital(0, "Berlin",			3664088).
capital(1, "Paris",			2240676).
capital(2, "Rome",			2870515).
capital(3, "Beijing",		21705033).
capital(4, "New Delhi",	9879234).
capital(5, "Washington",	601765).
capital(6, "Brasilia", 		2852395).
capital(7, "Canberra", 	410262).
capital(8, "Wellington", 	360677).
capital(9, "Cairo", 			8105079).

capital(10, "Pretoria", 	1815904).

/*represents(id_country, id_capital)*/
represents(0, 0).
represents(1, 1).
represents(2, 2).
represents(3, 3).
represents(4, 4).
represents(5, 5).
represents(6, 6).
represents(7, 7).
represents(8, 8).
represents(9, 9).

represents(10, 10).

/*Line: capitals("CapitalName", Part_of_world)*/
capitals(CapitalName, Part) :- 
    country(CountryId, _, Part, _),
    represents(CountryId, CapitalId),
    capital(CapitalId, CapitalName, _).

/*Line: present("CapitalName", "CountryName")*/
presents(CountryName, CapitalName) :-
    country(CountryId, CountryName, _, _),
    capital(CapitalId, CapitalName, _),
    represents(CountryId, CapitalId).

/*Line: popincapitals("CountryName", Count)*/
popincapitals(CountryName, CapitalPop) :-
    country(CountryId, CountryName, _, _),
    represents(CountryId, CapitalId),
    capital(CapitalId, _, CapitalPop).

/*Line: print()*/
print() :-
    country(_, CountryName, _, _),
    presents(CountryName, CapitalName),
    write(CountryName + " -> " + CapitalName), nl, fail.

/*
Запросы
1. capitals("CapitalName", Part_of_world)
Узнать часть света, в которой находится столица:
capitals("Berlin", Part)
capitals("Paris", Part)
Узнать, какие столицы расположены в данной части света:
capitals(Capital, europe)
Узнать столицы и части света, в которой они расположены:
capitals(Capital, Part)

2. present("CapitalName", "CountryName") 
По имени страны узнать ее столицу и наоборот:
presents("China", Capital)
presents(Country, "Beijing")
Узнать страны и их столицы:
presents(Country, Capital)

3. popincapitals("CountryName", Count)
По названию страны, узнать количество населения в ее столице:
popincapitals("Egypt", Count)

4. print()
Вывести все страны и их столицы:
print()
*/
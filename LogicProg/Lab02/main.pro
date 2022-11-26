% Copyright

implement main
    open core, stdio, file

domains
    part = australia; asia; america; antarctica; africa; europe.

class facts - worldDB
    country : (integer ID, string Name, part Part, integer Population) nondeterm.
    capital : (integer ID, string Name, integer Population) nondeterm.
    represents : (integer ID_country, integer ID_capital) nondeterm.

class predicates
    capitals : (string Name_Capital, part Part) nondeterm anyflow.
    presents : (string Name_Country, string Name_Capital) nondeterm anyflow.
    popincapitals : (string Name_Country, integer Capital_Population) nondeterm anyflow.
    print : ().

clauses
    capitals(CapitalName, Part) :-
        country(CountryId, _, Part, _),
        represents(CountryId, CapitalId),
        capital(CapitalId, CapitalName, _).

    presents(CountryName, CapitalName) :-
        country(CountryId, CountryName, _, _),
        capital(CapitalId, CapitalName, _),
        represents(CountryId, CapitalId).

    popincapitals(CountryName, CapitalPop) :-
        country(CountryId, CountryName, _, _),
        represents(CountryId, CapitalId),
        capital(CapitalId, _, CapitalPop).

    print() :-
        country(_, CountryName, _, _),
        presents(CountryName, CapitalName),
        write(CountryName, " -> ", CapitalName, "\n"),
        fail.
    print().

class facts
    capitalStats : (integer Max_ID, integer Min_ID, integer Count, integer Sumpop) single.

class predicates
    searchCapStat : ().
    mincap : (integer ID1, integer ID2, integer ID3 [out]).
    maxcap : (integer ID1, integer ID2, integer ID3 [out]).

clauses
    capitalStats(0, 0, 0, 0).

    mincap(ID1, ID2, ID1) :-
        capital(ID1, _, Count1),
        capital(ID2, _, Count2),
        Count1 <= Count2,
        !.
    mincap(_, ID2, ID2).

    maxcap(ID1, ID2, ID1) :-
        capital(ID1, _, Count1),
        capital(ID2, _, Count2),
        Count1 >= Count2,
        !.
    maxcap(_, ID2, ID2).

    searchCapStat() :-
        capital(ID, _, Pop),
        capitalStats(ID_Max, ID_Min, Count, Sum),
        maxcap(ID_Max, ID, New_ID_Max),
        mincap(ID_Min, ID, New_ID_Min),
        assert(capitalStats(New_ID_Max, New_ID_Min, Count + 1, Sum + Pop)),
        fail.
    searchCapStat() :-
        capitalStats(ID_Max, ID_Min, Count, Sumpop),
        capital(ID_Max, NameX, CountX),
        capital(ID_Min, NameN, CountN),
        write("Max Capital: ", NameX, " ", CountX),
        write("\nMin Capital: ", NameN, " ", CountN),
        write("\nCount Capital: ", Count),
        write("\nTotal Population: ", Sumpop),
        write("\nAverage Population: ", Sumpop / Count),
        nl,
        fail.
    searchCapStat().

clauses
    run() :-
        file::consult("../data.txt", worldDB),
        fail.

    run() :-
        capitals("Beijing", Part),
        write("Beijing --> ", Part, "\n"),
        capitals(Capital, europe),
        write(Capital, " --> europe \n"),
        fail.

    run() :-
        nl,
        presents("China", Capital),
        write("China --> ", Capital, "\n"),
        presents(Country, "Beijing"),
        write(Country, " --> Beijing \n"),
        fail.

    run() :-
        nl,
        popincapitals("Egypt", Count),
        write("Egypt --> Cap. Population: ", Count, "\n"),
        popincapitals(Country, 2852395),
        write(Country, " --> Cap. Population: 2852395 \n"),
        fail.

    run() :-
        nl,
        print(),
        fail.

    run() :-
        nl,
        searchCapStat(),
        fail.

    run().

end implement main

goal
    console::runUtf8(main::run).

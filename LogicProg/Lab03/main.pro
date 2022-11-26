% Copyright

implement main
    open core, stdio, file

domains
    part = australia; asia; america; antarctica; africa; europe.
    generalinfo = generalinfo(string CountryName, string CapitalName, part Part, integer Population).
    capitals = capitals(integer ID, string Name, integer Population).

class facts - worldDB
    country : (integer ID, string Name, part Part, integer Population).
    capital : (integer ID, string Name, integer Population).
    represents : (integer ID_country, integer ID_capital).

class predicates
    capitals : (part Part) -> string*.
    presents : (string CountryName) -> string CapitalName.
    popincapitals : (string CountryName) -> integer CapitalPopulation.

clauses
    capitals(Part) = Capitals :-
        Capitals =
            [ CapitalName ||
                country(CountryId, _, Part, _),
                represents(CountryId, CapitalId),
                capital(CapitalId, CapitalName, _)
            ].

    presents(CountryName) = CapitalName :-
        country(CountryId, CountryName, _, _),
        represents(CountryId, CapitalId),
        capital(CapitalId, CapitalName, _),
        !.
    presents(_) = "Unknown".

    popincapitals(CountryName) = CapitalPop :-
        country(CountryId, CountryName, _, _),
        represents(CountryId, CapitalId),
        capital(CapitalId, _, CapitalPop),
        !.
    popincapitals(_) = -1.

class predicates
    ginfo : () -> generalinfo* GInfo.
    printinfo : (generalinfo* Info).
    print : ().

clauses
    ginfo() = GInfo :-
        GInfo =
            [ generalinfo(CountryName, CapitalName, Part, Population) ||
                country(_, CountryName, Part, Population),
                CapitalName = presents(CountryName)
            ].

    printinfo([]).
    printinfo([Head | Tail]) :-
        generalinfo(CountryName, CapitalName, Part, Population) = Head,
        write(CountryName, ':\n'),
        writef("\tCapital: %\n\tPart: %\n\tPopulation: %\n", CapitalName, Part, Population),
        printinfo(Tail).

    print() :-
        GInfo = ginfo(),
        printinfo(Ginfo).

class predicates
    searchcapitalname : (capitals* CapitalList, integer ID) -> string CapitalName.
    presentsRE : (string CountryName) -> string CapitalName.

clauses
    searchcapitalname([], _) = "Unkonown".
    searchcapitalname([H | _], ID) = CapitalName :-
        capitals(ID, CapitalName, _) = H,
        !.
    searchcapitalname([_ | T], ID) = searchcapitalname(T, ID).

    presentsRE(CountryName) = CapitalName :-
        CapitalList = [ capitals(ID, Name, Population) || capital(ID, Name, Population) ],
        country(CountryId, CountryName, _, _),
        represents(CountryId, CapitalId),
        CapitalName = searchcapitalname(CapitalList, CapitalId),
        !.
    presentsRE(_) = "Unknown".

class predicates
    capitalstatistics : ().
    capitalscount : (capitals* CapitalList) -> integer Count.
    capitalspopulation : (capitals* CapitalList) -> integer SumPopulation.
    maxcapital : (capitals* CapitalList) -> string Name.
    mincapital : (capitals* CapitalList) -> string Name.

clauses
    capitalscount([]) = 0.
    capitalscount([_ | Tail]) = 1 + capitalscount(Tail).

    capitalspopulation([]) = 0.
    capitalspopulation([capitals(_, _, Population) | Tail]) = Population + capitalspopulation(Tail).

    maxcapital([capitals(_, Name, _)]) = Name :-
        !.
    maxcapital([Head | Tail]) = Name1 :-
        capitals(_, Name1, Population1) = Head,
        capital(_, maxcapital(Tail), Population2),
        Population1 > Population2,
        !.
    maxcapital([_ | Tail]) = maxcapital(Tail) :-
        !.
    maxcapital(_) = "Unknown".

    mincapital([capitals(_, Name, _)]) = Name :-
        !.
    mincapital([Head | Tail]) = Name1 :-
        capitals(_, Name1, Population1) = Head,
        capital(_, mincapital(Tail), Population2),
        Population1 < Population2,
        !.
    mincapital([_ | Tail]) = mincapital(Tail) :-
        !.
    mincapital(_) = "Unknown".

    capitalstatistics() :-
        CapitalList = [ capitals(ID, Name, Population) || capital(ID, Name, Population) ],
        CountCapitals = capitalscount(CapitalList),
        SumPopulation = capitalspopulation(CapitalList),
        write("Statistics of capitals:\n"),
        writef("\tCount: %\n\tTotal population: %\n\tAverage population: %\n", CountCapitals, SumPopulation, SumPopulation / CountCapitals),
        LargestCapital = maxcapital(CapitalList),
        LeastCapital = mincapital(CapitalList),
        writef("\tLargest capital: %\n\tLeast capital: %\n", LargestCapital, LeastCapital).

clauses
    run() :-
        file::consult("../data.txt", worldDB),
        fail.

    run() :-
        print(),
        nl,
        capitalstatistics(),
        nl,
        fail.

    run() :-
        Part = europe,
        Capitals = capitals(Part),
        write("Capitals in ", Part, ": ", Capitals, '\n'),
        nl,
        fail.

    run() :-
        CountryName = "China",
        CapitalName = presents(CountryName),
        CapitalPopulation = popincapitals(CountryName),
        writef("% is a capital of % with population %!\n", CapitalName, CountryName, CapitalPopulation),
        nl,
        fail.

    run() :-
        CountryName = "New Zealand",
        CapitalName = presentsRE(CountryName),
        writef("% is a capital of %!\n", CapitalName, CountryName),
        nl,
        fail.

    run().

end implement main

goal
    console::runUtf8(main::run).

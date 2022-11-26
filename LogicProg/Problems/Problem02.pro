% Copyright
% To practice on fail-loops and assert/retract predicates
% uses external data file 'problem02.data'

implement main
    open core, stdio, file

domains
    category = living; transport; food; other.

class facts - data
    spendings : (integer Spendings, category Category, integer Day, string Month).
    domain : (category Category).
    creport : (integer Total, integer DayCount) single.
    freport : (integer Total, integer DayCount) single.

class predicates
%    prints report with total / average spendings per day on this category over the given month
    categoryReport : (category Category, string Month).
%    prints full report with total / average spendings by category (and in general) over the given month
%    you may also implement a report of stats by date on the given month
    fullReport : (string Month).

clauses
    domain(living).
    domain(transport).
    domain(food).
    domain(other).

    creport(0, 0).
    categoryReport(Category, Month) :-
        assert(creport(0, 0)),
        spendings(Spendings, Category, _, Month),
        creport(Total, Count),
        assert(creport(Total + Spendings, Count + 1)),
        fail.
    categoryReport(Category, Month) :-
        creport(Total, Count),
        write("Month: ", Month, "\tCategory: ", Category, "\tTotal: ", Total, "\tAverage: ", Total / Count),
        nl.

    freport(0, 0).
    fullReport(Month) :-
        assert(freport(0, 0)),
        domain(Category),
        categoryReport(Category, Month),
        creport(Total_, Count_),
        freport(Total, Count),
        assert(freport(Total + Total_, Count + Count_)),
        fail.
    fullReport(Month) :-
        freport(Total, Count),
        write("Month: ", Month, "\tTotal: ", Total, "\tAverage: ", Total / Count),
        nl.

clauses
    run() :-
        file::consult("../problem02.data", data),
        fail.

    run() :-
        write("-----Category report-----\n"),
        categoryReport(transport, "April"),
        fail.

    run() :-
        nl,
        write("-----Full report-----\n"),
        fullReport("April"),
        fail.

    run().

end implement main

goal
    console::runUtf8(main::run).

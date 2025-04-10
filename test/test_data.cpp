#include "longnum.h"
#include <fstream>
#include <gtest/gtest.h>
#include <vector>

namespace bpm {
std::vector<LongInt> carmichael = {
    LongInt("561"),
    LongInt("1105"),
    LongInt("1729"),
    LongInt("2465"),
    LongInt("2821"),
    LongInt("6601"),
    LongInt("8911"),

    LongInt("41041"),
    LongInt("46657"),
    LongInt("52633"),
    LongInt("62745"),
    LongInt("63973"),
    LongInt("75361"),
    LongInt("101101"),
    LongInt("115921"),
    LongInt("126217"),
    LongInt("162401"),
    LongInt("172081"),
    LongInt("188461"),
    LongInt("252601"),
    LongInt("278545"),
    LongInt("294409"),
    LongInt("314821"),
    LongInt("334153"),
    LongInt("340561"),

    LongInt("321197185"),
    LongInt("413631505"),
    LongInt("5394826801"),
    LongInt("232250619601"),
    LongInt("9746347772161"),
    LongInt("1436697831295441"),
    LongInt("60977817398996785"),
    LongInt("7156857700403137441"),
    LongInt("1791562810662585767521"),

    LongInt("1590231231043178376951698401"),
    LongInt("2887148238050774106667593302092721"),
    LongInt("6553130926752006031481761"),
    LongInt("509033161838053437909477733201")};

std::vector<std::vector<LongInt>> composite = {
    {LongInt("77"), LongInt("91"), LongInt("119"), LongInt("143"),
     LongInt("221")},

    {LongInt("289"), LongInt("391"), LongInt("493"), LongInt("665"),
     LongInt("861")},

    {LongInt("1003"), LongInt("1197"), LongInt("1029"), LongInt("1073"),
     LongInt("1843")},

    {LongInt("10011"), LongInt("10395"), LongInt("11015"), LongInt("13039"),
     LongInt("14015")},

    {LongInt("100061"), LongInt("100441"), LongInt("101331"), LongInt("110561"),
     LongInt("120021")},

    {LongInt("1000001"), LongInt("1003009"), LongInt("1010001"),
     LongInt("1039601"), LongInt("1042921")},

    {LongInt("10000001"), LongInt("10000051"), LongInt("10009127"),
     LongInt("10052683"), LongInt("10107061")},

    {LongInt("100000003"), LongInt("100000021"), LongInt("100000191"),
     LongInt("100001001"), LongInt("100004139")},

    {LongInt("1000000001"), LongInt("1000000211"), LongInt("1000000343"),
     LongInt("1000000407"), LongInt("1000001229")},

    {LongInt("10000000031"), LongInt("10000000037"), LongInt("10000000071"),
     LongInt("10000000211"), LongInt("10000000321")},

    {LongInt("100000000009"), LongInt("100000000029"), LongInt("100000000031"),
     LongInt("100000000053"), LongInt("100000000113")},

    {LongInt("1000000000009"), LongInt("1000000000013"),
     LongInt("1000000000021"), LongInt("1000000000037")},

    {LongInt("10000000000019"), LongInt("10000000000097"),
     LongInt("10000000000061"), LongInt("10000000000073"),
     LongInt("10000000000103")},

    {LongInt("100000000000007"), LongInt("100000000000021"),
     LongInt("100000000000027"), LongInt("100000000000029"),
     LongInt("100000000000037")}};

std::vector<std::vector<LongInt>> primes = {
    {LongInt("13"), LongInt("17"), LongInt("19"), LongInt("23"), LongInt("29")},

    {LongInt("101"), LongInt("103"), LongInt("107"), LongInt("109"),
     LongInt("113")},

    {LongInt("1009"), LongInt("1013"), LongInt("1019"), LongInt("1021"),
     LongInt("1031")},

    {LongInt("10007"), LongInt("10009"), LongInt("10037"), LongInt("10039"),
     LongInt("10061")},

    {LongInt("100003"), LongInt("100019"), LongInt("100043"), LongInt("100049"),
     LongInt("100057")},

    {LongInt("1000003"), LongInt("1000033"), LongInt("1000037"),
     LongInt("1000039"), LongInt("1000081")},

    {LongInt("10000019"), LongInt("10000079"), LongInt("10000103"),
     LongInt("10000121"), LongInt("10000139")},

    {LongInt("100000007"), LongInt("100000037"), LongInt("100000039"),
     LongInt("100000073"), LongInt("100000081")},

    {LongInt("1000000007"), LongInt("1000000009"), LongInt("1000000021"),
     LongInt("1000000033"), LongInt("1000000087")},

    {LongInt("10000000019"), LongInt("10000000061")},

    {LongInt("1000000000039"), LongInt("100000000003"), LongInt("100000000019"),
     LongInt("100000000057"), LongInt("100000000063")},

    {LongInt("1000000000061"), LongInt("1000000000063")},

    {LongInt("10000000000037"), LongInt("10000000000051"),
     LongInt("10000000000099")},

    {LongInt("100000000000031"), LongInt("100000000000067"),
     LongInt("100000000000097"), LongInt("100000000000133")}};

std::vector<LongInt> big_primes = {

    LongInt("100000000000000000039"),
    LongInt("100000000000000000129"),

    LongInt("1000000000000000000000000000057"),
    LongInt("1000000000000000000000000000099"),

    LongInt("10000000000000000000000000000000000000121"),
    LongInt("10000000000000000000000000000000000000139"),

    LongInt("100000000000000000000000000000000000000000000000151"),
    LongInt("100000000000000000000000000000000000000000000000447"),

    LongInt("1000000000000000000000000000000000000000000000000000000000007"),
    LongInt("1000000000000000000000000000000000000000000000000000000000067"),

    LongInt("100000000000000000000000000000000000000000000000000000000000000000"
            "00033"),
    LongInt("100000000000000000000000000000000000000000000000000000000000000000"
            "00691"),

    LongInt("100000000000000000000000000000000000000000000000000000000000000000"
            "000000000000129"),
    LongInt("100000000000000000000000000000000000000000000000000000000000000000"
            "000000000000349"),

};

std::vector<LongInt> big_composite = {

    LongInt(LongInt("10000000019") * LongInt("10000000033")),
    LongInt(LongInt("10000000019") * LongInt("10000000061")),

    LongInt(LongInt("100000000000000000039") * LongInt("10000000033")),
    LongInt(LongInt("100000000000000000039") * LongInt("10000000061")),

    LongInt(LongInt("100000000000000000039") *
            LongInt("100000000000000000129")),
    LongInt(LongInt("100000000000000000039") *
            LongInt("100000000000000000151")),

    LongInt(LongInt("1000000000000000000000000000057") *
            LongInt("100000000000000000129")),
    LongInt(LongInt("1000000000000000000000000000057") *
            LongInt("100000000000000000151")),

    LongInt(LongInt("1000000000000000000000000000057") *
            LongInt("1000000000000000000000000000099")),
    LongInt(LongInt("1000000000000000000000000000057") *
            LongInt("1000000000000000000000000000211")),

    LongInt(LongInt("10000000000000000000000000000000000000121") *
            LongInt("1000000000000000000000000000099")),
    LongInt(LongInt("10000000000000000000000000000000000000121") *
            LongInt("1000000000000000000000000000211")),

    LongInt(LongInt("10000000000000000000000000000000000000121") *
            LongInt("10000000000000000000000000000000000000139")),
    LongInt(LongInt("10000000000000000000000000000000000000121") *
            LongInt("10000000000000000000000000000000000000301")),

};
} // namespace bpm
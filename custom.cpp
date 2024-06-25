#include "convert.hpp"
#include "Wordset.hpp"
#include "catch_amalgamated.hpp"
#include <vector>
#include <string>
#include <fstream>
#include "ver.hpp"


namespace {

TEST_CASE("xhashing basic", "[wordset-public]")
{
	unsigned hv = polynomialHashFunction("dbc", 37, 100000);
	unsigned shouldBe = 4*37*37 + 2*37 + 3;
	REQUIRE(hv == shouldBe);
}


TEST_CASE("xwordset basic isnert", "[wordset-public]")
{
	WordSet ws(11);
	ws.insert("dbc");
	REQUIRE(ws.contains("dbc"));
	REQUIRE(ws.getCapacity() == 11);
}


TEST_CASE("xwordset multiple insert", "[wordset-public]")
{
	WordSet ws(11);
	ws.insert("sleepy");
	ws.insert("happy");
	ws.insert("dopey");
	ws.insert("sneezy");
	ws.insert("datalink");
	ws.insert("australia");
	ws.insert("guacamole");
	ws.insert("phylum");
	REQUIRE(ws.contains("happy"));
	REQUIRE(ws.contains("dopey"));
	REQUIRE(ws.getCapacity() == 11);
}


TEST_CASE("xwordset resize", "[wordset-public]")
{
	WordSet ws(11);
	ws.insert("sleepy");
	ws.insert("happy");
	ws.insert("dopey");
	ws.insert("sneezy");
	ws.insert("datalink");
	ws.insert("australia");
	ws.insert("guacamole");
	ws.insert("phylum");
	REQUIRE(ws.contains("happy"));
	REQUIRE(ws.contains("dopey"));
	ws.insert("salsa");
	ws.insert("sloth");
	ws.insert("colossus");
	ws.insert("synergize");
	ws.insert("monday");
	ws.insert("tuesday");
	ws.insert("wednesday");
	ws.insert("thursday");
	ws.insert("friday");
	ws.insert("saturday");
	ws.insert("sunday");
	REQUIRE(ws.contains("monday"));
	REQUIRE(ws.contains("sunday"));
	REQUIRE(ws.getCapacity() == 23);
}

TEST_CASE("xAntToArt", "[convert-public]")
{
	WordSet words(11);
	std::ifstream in("words.txt");
	loadWordsIntoTable(words, in);

 	std::vector< std::string > r  = convert("ant", "art", words);

 	// this was a success if r was a valid conversion of length 2.
	std::ifstream in2("words.txt");
 	REQUIRE(r.size() == 2);
 	REQUIRE(  validConversion(r, "ant", "art", in2) );
}

TEST_CASE("AntToAunt", "[convert-custom]") {
        WordSet words(11);
        std::ifstream in("words.txt");
        loadWordsIntoTable(words, in);

        std::vector< std::string > r = convert("ant", "aunt", words);

        std::ifstream in2("words.txt");

        REQUIRE(r.size() == 0);
    }

    TEST_CASE("xxAntToAnt", "[convert-custom]") {
        WordSet words(11);
        std::ifstream in("words.txt");
        loadWordsIntoTable(words, in);

        std::vector< std::string > r = convert("ant", "ant", words);

        std::ifstream in2("words.txt");

        REQUIRE(r.size() == 1);
        REQUIRE(r[0] == "ant");
        REQUIRE(validConversion(r, "ant", "ant", in2));
    }

	TEST_CASE("nested resize", "[wordset-custom]") {
        // std::cout << "starting nested test\n";
        WordSet ws(1, 0);
        // std::cout << "inserting a\n";
        ws.insert("a");
        // std::cout << "inserting c\n";
        ws.insert("c");
        REQUIRE(ws.contains("a"));
        REQUIRE(ws.contains("c"));
        REQUIRE(ws.getCapacity() == 5);
        REQUIRE(ws.getCount() == 2);
    }

	TEST_CASE("wordset insert conflict", "[wordset-public]")
    {
        WordSet ws(11);
        ws.insert("aez");
        ws.insert("bdy");
        ws.insert("ccx");
        REQUIRE(ws.contains("aez"));
        REQUIRE(ws.contains("bdy"));
        REQUIRE(ws.contains("ccx"));
        REQUIRE(ws.getCapacity() == 23);
    }

	TEST_CASE("lazy hash - infinite loop check", "[wordset-public]")
    {
        WordSet ws(11);
        ws.insert("biographically");
        ws.insert("geographically");
        ws.insert("cryptographically");
        REQUIRE(ws.contains("biographically"));
        REQUIRE(ws.contains("geographically"));
        REQUIRE(ws.contains("cryptographically"));
    }
}
/*
    Written by  : Keith Brewer
    Date written: March 2012

    This program was written by me for an assignment in an advanced C++
    programming course. Each assignment had the option of being written for the
    console, as a FLTK GUI program, or as a Windows Forms program. I chose FLTK
    for this assignment because it sounded intriguing and was to be my first
    experience with GUI programming. 

    The requirements were:

    - Design a class to model the data in the Coordinates.xml file.
    - Design a string parsing class to extract the data between the xml tags,
      using regex to do so.
    - Store the data from the file in a map, set, or hash, using the class from
      the first point.
    - Design a query class to find two or more coordinates, then calculate the
      distance between them using the haversine formula. The haversine formula
      had to be used as a lambda expression.
    - Use polymorphism.

    I received full credit for the assignment and was one of very few people to
    turn in a GUI version of any assignment, especially one using FLTK.

    I found the ease with which I could develop a GUI based application to be 
    both exciting and useful. One downside was that FLTK does not do native look
    and feel (although that does also makes it very lightweight).


    This program was written using Visual Studio 2010.
*/

#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <regex>
#include <vector>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <unordered_map>
#include <cmath>

//FLTK includes
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>

#pragma warning(disable:4996)

const double DEG_TO_RAD   = 0.0174532925;
const double EARTH_RADIUS = 6371;

using namespace std;

/*
===============================================================================

    Parses a file with the general format below. In this example, the template
    class name would be "Coordinates" and the fieldCount would be 4. Since the
    parser just takes a regex pattern from the user, it should work with files
    that use [] or {} instead of just <>, like in this example. Any deviations
    from the general format below will probably make the parser explode. 

    <Coordinates>
        <Location>
            <Latitude>51.88</Latitude>
            <Longitude>176.65</Longitude>
            <City>Adak</City>
            <State>AK</State>
        </Location>
        <Location>
        .
        .
        .
        </Location>
        .
        .
        .
    </Coordinates>

===============================================================================
*/

template <typename type>
class Parser
{
private:
    int fieldCount;              //number of fields in each record
    regex pattern;               //regex pattern used to grab data between tags
    vector<type> parsedData;     //a vector of the fully parsed data
    vector<string> stringVector; //collects data between tags, until fieldCount is reached
    string fileName;
    fstream fileIn;

public:
    Parser(void);
    Parser(const string& pattern1, const int fields, const string& dataFileIn);
    ~Parser(void){}

    Parser(const Parser& rhsParser);

    Parser& operator=(const Parser& rhsParser);

    bool parseData      (Fl_Text_Display* parseTextDisplay);
    void setFieldCount  (const int n) {fieldCount = n;}

    type&         getData             (const int n) const {return parsedData[n];}
    int           getParsedVectorSize (void)        const {return parsedData.size();}
    vector<type>& getParsedVectorRef  (void) {return parsedData;}

};

/*
==============================
    Parser::Parser(void)

    Default constructor
==============================
*/
template <typename type>
Parser<type>::Parser(void)
    : fieldCount = 0,
      pattern(""),
      parsedData(0),
      stringVector(0),
      fileName(""),
{
}

/*
==============================
    Parser::Parser(string, int, string)

    Constructor that takes parameters for regex pattern, number of fields in
    each record of the file, and the file's name
==============================
*/
template <typename type>
Parser<type>::Parser(const string& pattern1, const int fields, const string& fileInName)
    : pattern(pattern1),
      fieldCount(fields),
      fileName(fileInName),
      parsedData(0),
      stringVector(0)
{
}

/*
==============================
    Parser::Parser(const Parser& rhsParser)

    Copy constructor
==============================
*/
template <typename type>
Parser<type>::Parser(const Parser& rhsParser)
{
    fieldCount    = rhsParser.fieldCount;
    pattern       = rhsParser.pattern;
    parsedData    = rhsParser.parsedData;
    stringVector  = rhsParser.stringVector;
    fileName      = rhsParser.fileName;
    fileIn        = rhsParser.fileIn;
}

/*
==============================
    Parser::operator=(const Parser& rhsParser)

    Overloaded assignment
==============================
*/
template <typename type>
Parser<type>& Parser<type>::operator=(const Parser& rhsParser)
{
    if(this == &rhsParser)
        return *this;

    fieldCount    = rhsParser.fieldCount;
    pattern       = rhsParser.pattern;
    parsedData    = rhsParser.parsedData;
    stringVector  = rhsParser.stringVector;
    fileName      = rhsParser.fileName;
    fileIn        = rhsParser.fileIn;

    return *this;
}

/*
==============================
    Parser::parseData

    Parses the data in the file from parser::fileName. Parameter is a fltk text
    display box used to keep the user up to date on the record parsing progress.
==============================
*/
template <typename type>
bool Parser<type>::parseData(Fl_Text_Display* parseTextDisplay)
{
    int parseCount = 0;
    int count      = 0;
    string filebuffString;
    string tokenString;        //string of tokens for one record, sent to "type"'s constructor
    sregex_token_iterator end;
    stringstream ss;           //used to hold tokens; i.e. data in fields
    stringstream outMessage;   //message for user, sent to fltk text display box
    char* outmess;             //because fltk requires a c style string

    fileIn.open(fileName);
    if(fileIn.fail()) //if the file could not be found/opened, inform the user
    {
        outMessage.clear();
        outMessage.str("");
        outMessage << "Could not open file.\n";
        outmess = new char[outMessage.str().size() + 1];
        strcpy(outmess, outMessage.str().c_str());
        parseTextDisplay->buffer()->append(outmess);
        delete [] outmess;
        return false;
    }

    while(getline(fileIn, filebuffString))
    {
        sregex_token_iterator tokens(filebuffString.begin(), filebuffString.end(), pattern);
        for(tokens; tokens != end; tokens++)
        { //from here until the if, grab the data from one field
            ss.clear(); //clear the stringstream for the next token
            ss.str(""); //make sure the internal string is clear too
            ss << *tokens; //send the current token to the stringstream
            tokenString = ss.str();
            tokenString.resize(tokenString.size() - 1); //regex pattern leaves a < on the
                                                        //end of the data, so get rid of it.
            stringVector.push_back(tokenString); //store token in a string vector
            count++;
            if(count == fieldCount) //when field count is reached, call "type"'s
            {                       //constructor, sending it the string vector
                parsedData.push_back(type(stringVector));
                stringVector.clear();   //all done, reset everything.
                count = 0;
                parseCount++;
                if(!(parseCount % 100)) //every 100 records, inform user of progress
                {
                    outMessage.clear();
                    outMessage.str("");
                    outMessage << "Parsed " << parseCount << " records....\n";
                    outmess = new char[outMessage.str().size() + 1];
                    strcpy(outmess, outMessage.str().c_str());
                    parseTextDisplay->buffer()->append(outmess);
                    Fl::check(); //to update the parsing progress text display
                    delete [] outmess;
                }
            }
        }
    }

    outMessage.clear();
    outMessage.str("");
    outMessage << parseCount << " records total.";  //final record count

    outmess = new char[outMessage.str().size() + 1];
    strcpy(outmess, outMessage.str().c_str());
    parseTextDisplay->buffer()->append(outmess);

    delete [] outmess;

    fileIn.close();

    return true;
}

/*
===============================================================================

    This class exists because the assignment required polymorphism. This made
    the most sense, considering. 

===============================================================================
*/
class Point
{
protected:
    double x;
    double y;

public:
    Point(void) : x(0.0), y(0.0) {}
    Point(const double newX, const double newY) : x(newX), y(newY) {}
    ~Point(void) {}

    Point(const Point& rhsPoint);

    Point& operator=(const Point& rhsPoint);

    virtual void setX(const double newX) {x = newX; return;}
    virtual void setY(const double newY) {y = newY; return;}
};

/*
==============================
    Point::(const Point& rhsPoint)

    Copy constructor
==============================
*/
Point::Point(const Point& rhsPoint)
{
    x = rhsPoint.x;
    y = rhsPoint.y;
}

/*
==============================
    Point::operator=(const Point& rhsPoint)

    Overloaded assignment
==============================
*/
Point& Point::operator=(const Point& rhsPoint)
{
    if(this == &rhsPoint)
        return *this;

    x = rhsPoint.x;
    y = rhsPoint.y;

    return *this;
}

/*
===============================================================================

    This is the class used to represent the city geo-coordinate data found in 
    the input file

===============================================================================
*/
class Coordinates : protected Point
{ /* FOLLOWING COMMENT BLOCK IS ORIGINAL TO THE ASSIGNMENT */
    //It's a stretch, but Point <- Coordinates is my attempt at polymorphism.
    //I figure it is borderline sensible because intersections on graph paper
    // are points with x and y values, spots in a 3D environment are points
    //with x and y values (the derived class adds a 'z' member), and
    //coordinates on a map are points with x and y values.

    //The references are used to make referring to x and y in the base class
    //more meaningful. Instead of trying to remember which coordinate goes with
    //'x' and which one goes with 'y', this is handled by the references, so 
    //someone using the Coordinates class can just say latitude and longitude
    //when writing code and not have to worry about x and y. The same could go
    //for any class that inherits from Point if they have special names for
    //the x and y concepts. 

    double& latitude;  //refers to Point::y after construction
    double& longitude; //refers to Point::x after construction
    string city;
    string state;

public:
    Coordinates(void);
    Coordinates(const vector<string>& rawDataIn);
    ~Coordinates(void) {}

    Coordinates(const Coordinates& rhsCoordinates);
    Coordinates& operator=(const Coordinates& rhsCoordinates);

    friend ostream& operator<<(ostream& os, const Coordinates& rhsCoordinates);

    double getLatitude  (void) const {return latitude;}
    double getLongitude (void) const {return longitude;}
    string getCity      (void) const {return city;}
    string getState     (void) const {return state;}
    void   setX         (const double newLongitude) {longitude = newLongitude; return;}
    void   setY         (const double newLatitude) {latitude = newLatitude; return;}

};

/*
==============================
    Coordinates::Coordinates

    Default constructor
==============================
*/
Coordinates::Coordinates(void) : Point(0.0, 0.0), latitude(y), longitude(x), city(""), state("")
{
}

/*
==============================
    Coordinates::Coordinates

    Constructor; assumes string contains proper data in proper order
==============================
*/
Coordinates::Coordinates(const vector<string>& rawDataIn) : Point(0.0, 0.0), latitude(y), longitude(x)
{
    stringstream ss;

    ss << rawDataIn[0];
    ss >> latitude;

    ss.clear();
    ss.str("");
    ss << rawDataIn[1];
    ss >> longitude;

    city = rawDataIn[2];
    state = rawDataIn[3];
}

/*
==============================
    Coordinates::Coordinates

    Copy constructor
==============================
*/
Coordinates::Coordinates(const Coordinates& rhsCoordinates) : Point(0.0, 0.0), latitude(y), longitude(x)
{
    setY(rhsCoordinates.latitude);
    setX(rhsCoordinates.longitude);

    city      = rhsCoordinates.city;
    state     = rhsCoordinates.state;
}

/*
==============================
    Coordinates::Coordinates

    Overloaded assignment
==============================
*/
Coordinates& Coordinates::operator=(const Coordinates& rhsCoordinates)
{
    if(this == &rhsCoordinates)
        return *this;

    setY(rhsCoordinates.latitude);
    setX(rhsCoordinates.longitude);

    city  = rhsCoordinates.city;
    state = rhsCoordinates.state;

    return *this;
}

/*
==============================
    Coordinates::operator<<

    overloaded insertion operator; outputs city name, state, lat., lon.
==============================
*/
ostream& operator<<(ostream& os, const Coordinates& rhsCoordinates)
{
    cout << rhsCoordinates.city << ", " << rhsCoordinates.state << endl;
    cout << "   latitude : " << setw(6) << rhsCoordinates.latitude << endl;
    cout << "   longitude: " << setw(6) << rhsCoordinates.longitude << "\n\n";

    return os;
}

//makes dealing with this a lot cleaner and shorter
typedef unordered_map<string, Coordinates>::const_iterator hashmapItem;

/*
===============================================================================

    This class exists because we were told to use either a set, map, or hash for
    this assignment. I chose a map, of the unordered variety. This unordered map
    is what actually stores the collection of Coordinates objects. 

===============================================================================
*/
class CoordHashMap
{
    unordered_map<string, Coordinates> hashmap;

public:
    CoordHashMap(void) {}
    CoordHashMap(const vector<Coordinates>& coordVec);
    ~CoordHashMap(void) {}

    friend class QueryDistance;

    CoordHashMap(const CoordHashMap& rhsCoordHashMap);
    CoordHashMap& operator=(const CoordHashMap& rhsCoordHashMap);

    unordered_map<string, Coordinates>& getHashmapRef(void) {return hashmap;}
};

/*
==============================
    CoordHashMap::CoordHashMap

    Constructor taking a Coordinate vector as a parameter. An unordered map is
    created from the contents of this vector
==============================
*/
CoordHashMap::CoordHashMap(const vector<Coordinates>& coordVec)
{
    Coordinates coordTemp;
    pair<hashmapItem, bool> retval;

    for(unsigned int i = 0; i < coordVec.size(); i++)
    {
        coordTemp = coordVec[i];
        retval = hashmap.insert(make_pair(coordTemp.getCity(), coordTemp));
    }
}

/*
==============================
    CoordHashMap::CoordHashMap

    Copy constructor
==============================
*/
CoordHashMap::CoordHashMap(const CoordHashMap& rhsCoordHashMap)
{
    hashmap = rhsCoordHashMap.hashmap;
}

/*
==============================
    CoordHashMap::CoordHashMap

    overloaded assignment
==============================
*/
CoordHashMap& CoordHashMap::operator=(const CoordHashMap& rhsCoordHashMap)
{
    if(this == &rhsCoordHashMap)
        return *this;

    hashmap    = rhsCoordHashMap.hashmap;

    return *this;
}

/*
===============================================================================

    This class is responsible for the haversine distance calculations between 2
    or more points (cities) on the Earth's surface. This class was required by
    the assignment. Also, the haversine distance calculation was specifically 
    required to be a lambda expression.

===============================================================================
*/
class QueryDistance
{
    double totalDistance;             //haversine distance between 2 or more cities
    CoordHashMap coordhashmap;        //using the CoordHashMap class
    vector<Coordinates> coordVector;  //vector of cities that the distance is being found for

public:
    QueryDistance(void) {}
    QueryDistance(const vector<Coordinates>& coordVec);
    ~QueryDistance(void) {}

    QueryDistance(const QueryDistance& rhsQueryDistance);
    QueryDistance& operator=(const QueryDistance& rhsQueryDistance);

    vector<Coordinates>& getCoordVector(void) {return coordVector;}

    void addCity          (Fl_Input* input, Fl_Text_Display* coordList);
    bool findOneCity      (Fl_Input* inputBox, Fl_Output* outputBox);
    void clearCurrentList (void) {coordVector.clear(); return;}
    void remakeHashMap    (const vector<Coordinates>& coordVec) {coordhashmap = coordVec; return;}
    int  coordVectorSize  (void) const {return coordVector.size();}

    template<typename type>
    void calcDistance(Fl_Text_Display* distOut, type func);
};

/*
==============================
    QueryDistance::QueryDistance

    Constructor taking a Coordinate vector as the parameter
==============================
*/
QueryDistance::QueryDistance(const vector<Coordinates>& coordVec)
{
    coordhashmap = coordVec;
}

/*
==============================
    QueryDistance::QueryDistance

    Copy constructor
==============================
*/
QueryDistance::QueryDistance(const QueryDistance& rhsQueryDistance)
{
    totalDistance = rhsQueryDistance.totalDistance;
    coordhashmap  = rhsQueryDistance.coordhashmap;
    coordVector   = rhsQueryDistance.coordVector;
}

/*
==============================
    QueryDistance::QueryDistance

    Overloaded assignment
==============================
*/
QueryDistance& QueryDistance::operator=(const QueryDistance& rhsQueryDistance)
{
    if(this == &rhsQueryDistance)
        return *this;

    totalDistance = rhsQueryDistance.totalDistance;
    coordhashmap  = rhsQueryDistance.coordhashmap;
    coordVector   = rhsQueryDistance.coordVector;

    return *this;
}

/*
==============================
    QueryDistance::addCity

    
==============================
*/
void QueryDistance::addCity(Fl_Input* input, Fl_Text_Display* coordList)
{
    hashmapItem hashSearch; //variable representing item in the unordered map 
    stringstream ss;        //for building city data to be sent to fltk display
    char* coordListValue;   //since fltk only works with c-style strings

    string cityToAdd(input->value());

    hashSearch = coordhashmap.hashmap.find(cityToAdd);  //find the city to add
    if(hashSearch != coordhashmap.hashmap.end()) //if city found, add to list of
    {                                            //cities being used in calculation
        coordVector.push_back(hashSearch->second);
        ss.clear();
        ss.str("");
        ss << hashSearch->second.getCity() << " ";
        ss << hashSearch->second.getState() << " ";
        ss << hashSearch->second.getLatitude() << " ";
        ss << hashSearch->second.getLongitude()<< "\n";
        coordListValue = new char[ss.str().size() + 1];
        strcpy(coordListValue, ss.str().c_str());
        coordList->buffer()->append(coordListValue); //fltk requires c-strings
        delete [] coordListValue;
    }

    return;
}

/*
==============================
    QueryDistance::findOneCity

    Looks for a city in the unordered map of Coordinates
==============================
*/
bool QueryDistance::findOneCity(Fl_Input* inputBox, Fl_Output* outputBox)
{
    hashmapItem hashSearch; //variable representing item in the unordered map 
    stringstream ss;        //for building city data to be sent to fltk display
    char* outputBoxValue;   //since fltk only works with c-style strings

    string targetCity = inputBox->value(); //city name typed into search field

    hashSearch = coordhashmap.hashmap.find(targetCity); //look for the city
    if(hashSearch != coordhashmap.hashmap.end()) //if found, show user
    {
        ss.clear();
        ss.str("");
        ss << hashSearch->second.getCity() << ", ";
        ss << hashSearch->second.getState() << ". ";
        ss << "Lat: " << hashSearch->second.getLatitude();
        ss << "   Lon: " << hashSearch->second.getLongitude();
        outputBoxValue = new char[ss.str().size() + 1];
        strcpy(outputBoxValue, ss.str().c_str());
        outputBox->value(outputBoxValue);
        delete [] outputBoxValue;
        return true;
    }
    else //if not found, let them know as much
    {
        ss.clear();
        ss.str("");
        ss << targetCity << " was not found in the list.";
        outputBoxValue = new char[ss.str().size() + 1];
        strcpy(outputBoxValue, ss.str().c_str());
        outputBox->value(outputBoxValue);
        delete [] outputBoxValue;
        return false;
    }

    return false;
}

/*
==============================
    QueryDistance::calcDistance

    The real meat. "type" here is a lambda expression, as required by the
    assignment. The distance is calculated using the Haversine formula, which
    finds the distance between two points on a sphere.
==============================
*/
template<typename type>
void QueryDistance::calcDistance(Fl_Text_Display* distOut, type func)
{
    stringstream ss;
    char* distanceValue; //like always, fltk required c-string

    totalDistance = func(coordVector); // <-- the magic happens in func

    ss.clear();
    ss.str("");
    distOut->buffer()->text("");

    ss << totalDistance << " km\n";
    ss << totalDistance * 0.621371192 << " mi\n";

    distanceValue = new char[ss.str().size() + 1];
    strcpy(distanceValue, ss.str().c_str());
    distOut->buffer()->append(distanceValue);
    delete [] distanceValue;

    return;
}

/*
===============================================================================

    The purpose of MainWindow is to hold all of the fltk GUI widgets and 
    functionality.

===============================================================================
*/
class MainWindow : public Fl_Window
{
    static void parse_cb     (Fl_Widget* parseButton, void* mainWindow);
    static void search_cb    (Fl_Widget* searchButton, void* mainWindow);
    static void addToList_cb (Fl_Widget* addButton, void* mainWindow);
    static void clearList_cb (Fl_Widget* clearListButton, void* mainWindow);
    static void calcDist_cb  (Fl_Widget* calcDistButton, void* mainWindow);

    Parser<Coordinates>& parse;
    QueryDistance& query;

public:
    MainWindow(int width, int height, const char* title, Parser<Coordinates>& parse, QueryDistance& query);
    ~MainWindow(void){}

    //parse
    Fl_Button*       parseButton;
    Fl_Text_Display* parseTextDisplay; //to show progress of file parsing

    //search
    Fl_Input*  searchInput;   //input text field
    Fl_Output* searchOutput;  //output text field
    Fl_Button* searchButton;
    Fl_Button* addCityButton;

    //coordinate list
    Fl_Text_Display* coordList; //text display to show list of cities in calculation
    Fl_Button* clearListButton; // ^--- clear this list

    //distance calculation result
    Fl_Text_Display* distanceOutput; //show the calculated distance
    Fl_Button*       calcDistButton;


};

/*
==============================
    MainWindow::MainWindow

    Constructor
==============================
*/
MainWindow::MainWindow(int width, int height, const char* title, Parser<Coordinates>& parser, QueryDistance& qd)
    : Fl_Window(width, height, title),
      parse(parser),
      query(qd)
{
    color(FL_GRAY);

    begin(); //tell fltk to begin building the interface for this particular window
    //parsing widgets
        parseButton = new Fl_Button(25,15,90,20, "&Parse");
        parseButton->callback(parse_cb, this);

        parseTextDisplay = new Fl_Text_Display(25, 40, 220, 220, "Parse Results");
        parseTextDisplay->buffer(new Fl_Text_Buffer());
        parseTextDisplay->align(FL_ALIGN_BOTTOM | FL_ALIGN_LEFT);


    //searching widgets
        searchInput   = new Fl_Input(300, 40, 270, 20, "");
        searchButton  = new Fl_Button(580, 40, 90, 20, "&Search");
        searchOutput  = new Fl_Output(300, 62, 270, 20, "");
        addCityButton = new Fl_Button(580, 62, 90, 20, "&Add");

        searchInput->callback(search_cb, this);
        searchInput->when(FL_WHEN_RELEASE | FL_WHEN_ENTER_KEY); /* when search input box
    loses focus or when or when the enter key is pressed, fire off the callback */

        searchButton->callback(search_cb, this);
        searchButton->deactivate();

        addCityButton->callback(addToList_cb, this);
        addCityButton->deactivate();

    //coordinate list
        coordList = new Fl_Text_Display(300, 116, 270, 110, "Current Coordinate List");
        coordList->buffer(new Fl_Text_Buffer());
        coordList->align(FL_ALIGN_TOP | FL_ALIGN_LEFT);

        clearListButton = new Fl_Button(580, 116, 90, 20, "&Clear List");
        clearListButton->callback(clearList_cb, this);
        clearListButton->deactivate();

    //distance calculation output
        distanceOutput = new Fl_Text_Display(300, 262, 220, 55, "Total Haversine Distance");
        distanceOutput->buffer(new Fl_Text_Buffer());
        distanceOutput->align(FL_ALIGN_TOP | FL_ALIGN_LEFT);

        calcDistButton = new Fl_Button(530, 262, 130, 20, "Calculate &Distance");
        calcDistButton->callback(calcDist_cb, this);
        calcDistButton->deactivate();

    end(); //let fltk know that interface building for this window is done

    show(); //show the window on the screen
}

/*
==============================
    MainWindow::parse_cb

    The callback function for the parse button widget. When the parse button is
    pressed, the input file is parsed. Along the way, parsing progress through
    the file is shown in a multiline text display box
==============================
*/
void MainWindow::parse_cb(Fl_Widget* parseButton, void* mainWindow)
{
    MainWindow* mainwin = (MainWindow*)mainWindow;
    Fl_Button*  button  = (Fl_Button*)parseButton;

    Fl_Text_Display* outMulti = mainwin->parseTextDisplay;
    button->deactivate();

    outMulti->buffer()->text("");

    if(mainwin->parse.parseData(outMulti))
    {
        mainwin->query.remakeHashMap(mainwin->parse.getParsedVectorRef());
        mainwin->searchButton->activate();
    }
    else
        button->activate();
}

/*
==============================
    MainWindow::search_cb

    The callback function for the search button. When the search button is
    pressed, the query class is called to find the target city in the unordered
    map. If found, the add button is activated. Otherwise, make sure the add
    button is deactivated.
==============================
*/
void MainWindow::search_cb(Fl_Widget* searchButton, void* mainWindow)
{
    MainWindow* mainwin = (MainWindow*)mainWindow;
    Fl_Button*  button  = (Fl_Button*)searchButton;

    if(mainwin->query.findOneCity(mainwin->searchInput, mainwin->searchOutput))
        mainwin->addCityButton->activate();
    else
        mainwin->addCityButton->deactivate();
}

/*
==============================
    MainWindow::addToList_cb

    The callback function for the add button. Adds the city being searched for
    (if found) to the list of cities to calculate distance for. 
==============================
*/
void MainWindow::addToList_cb(Fl_Widget* addButton, void* mainWindow)
{
    MainWindow* mainwin = (MainWindow*)mainWindow;
    Fl_Button*  button  = (Fl_Button*)addButton;

    mainwin->query.addCity(mainwin->searchInput, mainwin->coordList);

    if(mainwin->query.coordVectorSize()) //if something in list, activate clear button
        mainwin->clearListButton->activate();

    if((mainwin->query.coordVectorSize()) > 1) //only activate calculate button
        mainwin->calcDistButton->activate();   //if at least 2 cities in list

    return;
}
    
/*
==============================
    MainWindow::clearList_cb

    Clears the text display box that shows the current list of cities in the 
    distance calculation. 
==============================
*/
void MainWindow::clearList_cb(Fl_Widget* clearListButton, void* mainWindow)
{
    MainWindow* mainwin = (MainWindow*)mainWindow;
    Fl_Button*  button  = (Fl_Button*)clearListButton;

    mainwin->query.clearCurrentList();
    mainwin->coordList->buffer()->text("");
    button->deactivate();
    mainwin->distanceOutput->buffer()->text("");
    mainwin->calcDistButton->deactivate();

    return;
}

/*
==============================
    MainWindow::calcDist_cb

    The callback function for the calculate distance button. When the calculate
    distance button is pressed, the calculation is performed using the lambda
    expression starting on the 6th line of this function using the haversine
    distance calculation contained in the lambda function body.
==============================
*/
void MainWindow::calcDist_cb(Fl_Widget* calcDistButton, void* mainWindow)
{
    MainWindow* mainwin = (MainWindow*)mainWindow;
    Fl_Button*  button  = (Fl_Button*)calcDistButton;

    mainwin->query.calcDistance(mainwin->distanceOutput, [](vector<Coordinates> cv) -> double {
    double total = 0.0;
    for(unsigned i = 0; i < (cv.size() - 1); i++)
    {
        double deltaLat = abs(cv[i].getLatitude() - cv[i + 1].getLatitude()) * DEG_TO_RAD;
        double deltaLon = abs(cv[i].getLongitude() - cv[i + 1].getLongitude()) * DEG_TO_RAD;
        double lat1 = cv[i].getLatitude() * DEG_TO_RAD;
        double lat2 = cv[i + 1].getLatitude() * DEG_TO_RAD;

        double a = sin(deltaLat / 2) * sin(deltaLat / 2) +
                   sin(deltaLon / 2) * sin(deltaLon / 2) * cos(lat1) * cos(lat2);
        double c = 2.0 * atan2(sqrt(abs(a)), sqrt(abs(1 - a)));
        double d = EARTH_RADIUS * c;

        total += d;
    }
        return total;
    });

    return;
}

/*
===============================================================================

    Obvious...

===============================================================================
*/
int main(void)
{
    {
        Parser<Coordinates> parser("(?! >)(?! )[^>]+<", 4, "Coordinates.xml");
        QueryDistance query(parser.getParsedVectorRef());
    
        MainWindow window(700, 350, "Haversine Distance", parser, query);

        Fl::run();
    }

    return 0;
}

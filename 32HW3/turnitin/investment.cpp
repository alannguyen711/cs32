
class Investment
{
public:
    string name() const
    { return m_name; }
    
    virtual bool fungible() const
    { return false; }
    
    virtual string description() const = 0;
    
    int purchasePrice() const
    { return m_purchasePrice; }
    Investment(string i_name, int i_purch): m_name(i_name),  m_purchasePrice(i_purch)
    {}
    virtual ~Investment()
    {}
private:
    string m_name;
    int m_purchasePrice;
};

class Painting: public Investment // (name, purchase price)
{
public:
    virtual string description() const// virtual, all descriptions look different
    { return "painting"; }// what should I return?
    Painting(string i_name, int i_purch): Investment(i_name, i_purch)
    {}
    virtual ~Painting()
    { cout << "Destroying " + name() + ", a painting" << endl; }
    // Destroying Salvator Mundi, a painting
private:
    // Salvator Mundi: painting bought for $450300000
};

class Stock: public Investment // name, purchase price, description
{
public:
    virtual string description() const // virtual, all descriptions look different
    { return "stock trading as " + m_stockName; }
    virtual bool fungible() const // should be virtual, only stocks fungible
    { return true; }
    Stock(string i_name, int i_purch, string i_stockName):
    Investment(i_name, i_purch),  m_stockName(i_stockName)
    {}
    virtual ~Stock()
    { cout << "Destroying " + name() + ", stock holding" << endl; }
    // Destroying Lyft, a stock holding
private:
    string m_stockName;
    // Lyft (fungible): stock trading as LYFT bought for $50000
};

class House: public Investment // name, purchase price
{
public:
    virtual string description() const // virtual, all descriptions look different
    { return "house"; }
    House(string i_name, int i_purch): Investment(i_name, i_purch)
    {}
    virtual ~House()
    { cout << "Destroying the house " + name() << endl; }
    // Destroying the house 4 Privet Drive
private:
    
    //4 Privet Drive: house bought for $660000
};

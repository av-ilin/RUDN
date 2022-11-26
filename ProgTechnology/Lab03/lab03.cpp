#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

class Point
{
public:
    Point() {}

    virtual double get_x() const = 0;
    virtual double get_y() const = 0;
    virtual double get_z() const {}

    virtual void set_x(double x_) = 0;
    virtual void set_y(double y_) = 0;
    virtual void set_z(double z_) {}

    virtual void print() const = 0;

protected:
    virtual ~Point() {}

};

class Point2D : public Point
{
private:
    double x,y;
public:
    Point2D(){
        x = 0;
        y = 0;
    }

    Point2D(double x_, double y_){
        x = x_;
        y = y_;

    }
    double get_x() const override { return x; }
    double get_y() const override { return y; }

    void set_x(double x_) override { x = x_; }
    void set_y(double y_) override { y = y_; }

    void print() const override { cout << "Point2D: " << '(' << x << ", " << y << ')' << endl;}

    ~Point2D() override {}
};

class Point3D : public Point
{
private:
    double x, y, z;
public:
    Point3D(){
        x = 0;
        y = 0;
        z = 0;
    }

    Point3D(double x_, double y_,  double z_){
        x = x_;
        y = y_;
        z = z_;
    }

    double get_x() const override { return x; }
    double get_y() const override { return y; }
    double get_z() const override { return z; }

    void set_x(double x_) override { x = x_; }
    void set_y(double y_) override { y = y_; }
    void set_z(double z_) override { z = z_; }

    void print() const override { cout << "Point3D: " << '(' << x << ", " << y << ", " << z << ')' << endl;}

    ~Point3D() override {}
};

class Figure
{
protected:
    string name;
    vector<Point*> plenty;
    virtual ~Figure() {}

public:
    Figure(){}

    Figure(const Figure &other)
    {
        cout<<"Called Figure copy constructor!\n";
        this->name = other.name;
        this->plenty = other.plenty;
    }

    string get_name() const {return name;}
    void set_name(string name_){name = name_;}

    vector<Point*> get_plenty() const {return plenty;}
    void set_plenty(const vector<Point*> &other_plenty){plenty = other_plenty;}

    void print() const
    {
        cout << "Points of " << name << endl;
        for (int i = 0; i < plenty.size(); i++)
            plenty[i]->print();
    }

    virtual bool check() = 0;
    virtual double svf() = 0;
    virtual double per() = 0;
};

double len(double x1, double y1, double x2, double y2)
{
    double l = sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
    return l;
}

class Triangle : public Figure
{
private:
    Point2D a;
    Point2D b;
    Point2D c;

public:
    Triangle(): a(0,0), c(2, 2), b(4,0)
    {
        plenty = {&a, &b, &c};
        name = "Unnamed Triangle";
        cout << "Triangle "<< name << " is created of default  !" << endl;
    }

    Triangle(string name_, vector<Point*> &plenty_)
    {
        name = name_;
        plenty = plenty_;
        cout << "Triangle " << name << " is created!" << endl;
    }

    bool check() override
    {
        if (    ( plenty[1]->get_x() - plenty[0]->get_x()) * ( plenty[2]->get_y() - plenty[0]->get_y() ) !=
                ( plenty[2]->get_x() - plenty[0]->get_x() ) *( plenty[1]->get_y() - plenty[0]->get_y() )    )
            return true;
        else
            return false;
    }

    double svf() override
    {
        double s(-1);
        if (check())
            s = 0.5 * abs(    ( plenty[1]->get_x() - plenty[0]->get_x()) *
                              ( plenty[2]->get_y() - plenty[0]->get_y() ) -
                              ( plenty[2]->get_x() - plenty[0]->get_x() ) *
                              ( plenty[1]->get_y() - plenty[0]->get_y() )    );
        return s;
    }
    double per() override
    {
        double p(0);
        if (check())
        {
            for (int i = 0; i < 3; i++)
                p += len(plenty[i]->get_x(), plenty[i]->get_y(),
                         plenty[(i + 1) % 3]->get_x(), plenty[(i + 1) % 3]->get_y() );
            return p;
        }
        else
            return -1;
    }

    ~Triangle()
    {
        cout << "Triangle " << name << " is deleted!" << endl;
    }
};

class Circle : public Figure
{
private:
    Point2D a;
    Point2D b;

public:
    Circle(): a(0,0), b(1, 1)
    {
        plenty = {&a, &b};
        name = "Unnamed Circle";
        cout << "Circle " << name << " is created of default!" << endl;
    }

    Circle(string name_, vector<Point*> &plenty_)
    {
        name = name_;
        plenty = plenty_;
        cout << "Circle " << name << " is created!" << endl;
    }

    bool check() override
    {
        double x1, y1, x2, y2;
        x1 = plenty[0]->get_x();
        y1 = plenty[0]->get_y();
        x2 = plenty[1]->get_x();
        y2 = plenty[1]->get_y();

        if (x1 != x2 && y1 != y2)
            return true;
        else
            return false;
    }

    double svf() override
    {
        if (check())
        {
            double pi = atan(1) * 4;
            double r = len( plenty[0]->get_x(), plenty[0]->get_y(), plenty[1]->get_x(), plenty[1]->get_y() );
            double s = r * r * pi;
            return s;
        }
        else
            return -1;

    }

    double per() override
    {
        if (check())
        {
            double pi = atan(1) * 4;
            double r = len(plenty[0]->get_x(), plenty[0]->get_y(), plenty[1]->get_x(), plenty[1]->get_y() );
            double l = 2 * r * pi;
            return l;
        }
        else
            return -1;
    }

    ~Circle()
    {
        cout << "Circle " << name << " is deleted!" << endl;
    }
};

class Rectangle : public Figure
{
private:
    Point2D a;
    Point2D b;
    Point2D c;
    Point2D d;
public:
    Rectangle(): a(0,0), b(2, 0), c(2, 1), d(0, 1)
    {
        plenty = {&a, &b, &c, &d};
        name = "Unnamed Rectangle";
        cout << "Rectangle " << name << " is created of default!" << endl;
    }

    Rectangle(string name_, vector<Point*> &plenty_)
    {
        name = name_;
        plenty = plenty_;
        cout << "Rectangle " << name << " is created!" << endl;
    }

    bool check() override
    {
        bool b = true;
        if (plenty[0]->get_y() != plenty[1]->get_y())
            b = false;

        if (plenty[1]->get_x() != plenty[2]->get_x())
            b = false;

        if (plenty[3]->get_y() != plenty[2]->get_y())
            b = false;

        if (plenty[3]->get_x() != plenty[0]->get_x())
            b = false;

        return b;
    }

    double svf() override
    {
        if(check())
        {
            double a = len( plenty[0]->get_x(), plenty[0]->get_y(), plenty[1]->get_x(), plenty[1]->get_y() );
            double b = len( plenty[0]->get_x(), plenty[0]->get_y(), plenty[3]->get_x(), plenty[3]->get_y() );

            double s = a * b;
            return s;
        }
        else
            return -1;
    }
    double per() override
    {
        if(check())
        {
            double a = len( plenty[0]->get_x(), plenty[0]->get_y(), plenty[1]->get_x(), plenty[1]->get_y() );
            double b = len( plenty[0]->get_x(), plenty[0]->get_y(), plenty[3]->get_x(), plenty[3]->get_y() );

            double p = (a + b) * 2;
            return p;
        }
        else
            return -1;

    }

    ~Rectangle()
    {
        cout << "Rectangle " << name << " is deleted!" << endl;
    }
};

double len3D(double x1, double y1, double z1, double x2, double y2, double z2)
{
    double l = sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2) + pow((z2 - z1), 2));
    return l;
}

class Sphere : public Figure
{
private:
    Point3D a;
    Point3D b;

public:
    Sphere(): a(0,0,0), b(0, 0, 1)
    {
        plenty = {&a, &b};
        name = "Unnamed Sphere";
        cout << "Sphere " << name << " is created of default!" << endl;
    }

    Sphere(string name_, vector<Point*> &plenty_)
    {
        name = name_;
        plenty = plenty_;
        cout << "Sphere " << name << " is created!" << endl;
    }

    bool check() override
    {
        double x1, y1, z1, x2, y2, z2;
        x1 = plenty[0]->get_x();
        y1 = plenty[0]->get_y();
        z1 = plenty[0]->get_z();
        x2 = plenty[1]->get_x();
        y2 = plenty[1]->get_y();
        z2 = plenty[1]->get_z();
        if (x1 != x2 && y1 != y2 && z1 != z2)
            return true;
        else
            return false;
    }

    double svf() override
    {
        if(check())
        {
            double pi = atan(1) * 4;
            double r = len3D(   plenty[0]->get_x(), plenty[0]->get_y(), plenty[0]->get_z(),
                                plenty[1]->get_x(), plenty[1]->get_y(), plenty[1]->get_z()    );
            double v = 4 / 3.0 * pi * r * r * r;
            return v;
        }
        else
            return -1;

    }
    double per() override
    {
        if(check())
        {
            double pi = atan(1) * 4;
            double r = len3D(   plenty[0]->get_x(), plenty[0]->get_y(), plenty[0]->get_z(),
                                plenty[1]->get_x(), plenty[1]->get_y(), plenty[1]->get_z()    );
            double s = 4 * pi * r * r;
            return s;
        }
        else
            return -1;
    }

    ~Sphere()
    {
        cout << "Sphere " << name << " is deleted!" << endl;
    }
};

class Tetrahedron : public Figure
{
private:
    Point3D a;
    Point3D b;
    Point3D c;
    Point3D d;

public:
    Tetrahedron(): a(0,0,0), b(1, 0, 0), c(1/2.0, sqrt(3)/2.0, 0), d(1/2.0, sqrt(3)/6.0, sqrt(2)/sqrt(6))
    {
        plenty = {&a, &b, &c, &d};
        name = "Unnamed Tetrahedron";
        cout << "Tetrahedron " << name << " is created of default!" << endl;
    }

    Tetrahedron(string name_, vector<Point*> &plenty_)
    {
        name = name_;
        plenty = plenty_;
        cout << "Tetrahedron " << name << " is created!" << endl;
    }

    bool check() override
    {
        return true;
    }

    double svf() override
    {
        double a = len3D(   plenty[0]->get_x(), plenty[0]->get_y(), plenty[0]->get_z(),
                            plenty[1]->get_x(), plenty[1]->get_y(), plenty[1]->get_z()    );

        double v = a * a * a * sqrt(2) / 12.0;
        return v;
    }
    double per() override
    {
        double a = len3D(   plenty[0]->get_x(), plenty[0]->get_y(), plenty[0]->get_z(),
                            plenty[1]->get_x(), plenty[1]->get_y(), plenty[1]->get_z()    );

        double s = a * sqrt(3);
        return s;
    }

    ~Tetrahedron()
    {
        cout << "Tetrahedron " << name << " is deleted!" << endl;
    }
};

class Parallelepiped : public Figure
{
private:
    Point3D a;
    Point3D b;
    Point3D c;
    Point3D d;
    Point3D a1;
    Point3D b1;
    Point3D c1;
    Point3D d1;

public:
    Parallelepiped(): a(0,0,0), b(1,0,0), c(1,1,0), d(0,1,0),
                      a1(0,0,1), b1(1,0,1), c1(1,1,1), d1(0,1,1)
    {
        plenty = {&a, &b, &c, &d, &a1, &b1, &c1, &d1};
        name = "Unnamed Parallelepiped";
        cout << "Parallelepiped " << name << " is created of default!" << endl;
    }

    Parallelepiped(string name_, vector<Point*> &plenty_)
    {
        name = name_;
        plenty = plenty_;
        cout << "Parallelepiped " << name << " is created!" << endl;
    }

    bool check() override
    {
        return true;
    }

    double svf() override
    {
        double a = len3D(   plenty[0]->get_x(), plenty[0]->get_y(), plenty[0]->get_z(),
                            plenty[1]->get_x(), plenty[1]->get_y(), plenty[1]->get_z()    );

        double b = len3D(   plenty[0]->get_x(), plenty[0]->get_y(), plenty[0]->get_z(),
                            plenty[3]->get_x(), plenty[3]->get_y(), plenty[3]->get_z()    );

        double c = len3D(   plenty[0]->get_x(), plenty[0]->get_y(), plenty[0]->get_z(),
                            plenty[4]->get_x(), plenty[4]->get_y(), plenty[4]->get_z()    );

        double v = a * b * c;
        return v;
    }

    double per() override
    {
        double a = len3D(   plenty[0]->get_x(), plenty[0]->get_y(), plenty[0]->get_z(),
                            plenty[1]->get_x(), plenty[1]->get_y(), plenty[1]->get_z()    );

        double b = len3D(   plenty[0]->get_x(), plenty[0]->get_y(), plenty[0]->get_z(),
                            plenty[3]->get_x(), plenty[3]->get_y(), plenty[3]->get_z()    );

        double c = len3D(   plenty[0]->get_x(), plenty[0]->get_y(), plenty[0]->get_z(),
                            plenty[4]->get_x(), plenty[4]->get_y(), plenty[4]->get_z()    );

        double s = 2 * (a*c + c*b + a*b);
        return s;
    }

    ~Parallelepiped()
    {
        cout << "Parallelepiped " << name << " is deleted!" << endl;
    }
};

/*
bool tr_inter(const Triangle &t1, const Triangle &t2)
{
    vector<Point*> t = t1.get_plenty();
    vector<Point*> t_ = t2.get_plenty();

    for(int i = 0; i < 3; i++)
    {

        double a =( (t[0]->get_x() - t_[i]->get_x()) * (t[1]->get_y() - t[0]->get_y()) -
                    (t[0]->get_y() - t_[i]->get_y()) * (t[1]->get_x() - t[0]->get_x())   );

        double b =( (t[1]->get_x() - t_[i]->get_x()) * (t[2]->get_y() - t[1]->get_y()) -
                    (t[1]->get_y() - t_[i]->get_y()) * (t[2]->get_x() - t[1]->get_x())   );

        double c =( (t[2]->get_x() - t_[i]->get_x()) * (t[0]->get_y() - t[2]->get_y()) -
                    (t[2]->get_y() - t_[i]->get_y()) * (t[0]->get_x() - t[2]->get_x())   );

        if ((a >= 0 && b >= 0 && c >= 0) || (a <= 0 && b <= 0 && c <= 0))
            return true;



        a = (       (t_[0]->get_x() - t[i]->get_x()) * (t_[1]->get_y() - t_[0]->get_y()) -
                    (t_[0]->get_y() - t[i]->get_y()) * (t_[1]->get_x() - t_[0]->get_x())   );

        b =(        (t_[1]->get_x() - t[i]->get_x()) * (t_[2]->get_y() - t_[1]->get_y()) -
                    (t_[1]->get_y() - t[i]->get_y()) * (t_[2]->get_x() - t_[1]->get_x())   );

        c =(        (t_[2]->get_x() - t[i]->get_x()) * (t_[0]->get_y() - t_[2]->get_y()) -
                    (t_[2]->get_y() - t[i]->get_y()) * (t_[0]->get_x() - t_[2]->get_x())   );

        if ((a >= 0 && b >= 0 && c >= 0) || (a <= 0 && b <= 0 && c <= 0))
            return true;

    }

    return false;
};
*/
int main()
{
    Triangle t0;
    t0.print();

    //Point* a = new Point2D, *b = new Point2D(3, 0), *c = new Point2D(0, 4);
    //Point* a = new Point2D(2, 0), *b = new Point2D(3, 2), *c = new Point2D(4, 0);
    //Point* a = new Point2D(3, 0), *b = new Point2D(3, 2), *c = new Point2D(4, 0);
    //Point* a = new Point2D(3, 1), *b = new Point2D(5, 1), *c = new Point2D(3, 3);
    Point* a = new Point2D(3.1, 1), *b = new Point2D(5, 1), *c = new Point2D(3, 3);
    vector<Point*> tv = {a, b, c};
    Triangle t1("Pines", tv);
    t1.print();




    /*
    if(tr_inter(t0, t1))
        cout << t0.get_name() << " and " << t1.get_name() << " is intersect!" << endl;
    else
        cout << t0.get_name() << " and " << t1.get_name() << " is not intersect!" << endl;

    if(tr_inter(t1, t0))
        cout << t0.get_name() << " and " << t1.get_name() << " is intersect!" << endl;
    else
        cout << t0.get_name() << " and " << t1.get_name() << " is not intersect!" << endl;
    */





    Triangle t2(t0);
    t2.print();

    t2.set_name(t1.get_name());
    t2.set_plenty(t1.get_plenty());
    t2.print();

    cout << t2.get_name() << ' ' << "S: " <<  t2.svf()<< "\t" << "P: " << t2.per() << endl;
    cout << t0.get_name() << ' ' << "S: " <<  t0.svf()<< "\t" << "P: " << t0.per() << endl;
    cout << "---------------------------------------" << endl << endl;

    Circle c0;
    c0.print();

    Point2D a1, b1(3, 0);
    vector<Point*> cv = {&a1, &b1};
    Circle c1("Andrew", cv);
    c1.print();

    Circle c2(c0);
    c2.print();

    c2.set_name(c1.get_name());
    c2.set_plenty(c1.get_plenty());
    c2.print();

    cout << c2.get_name() << ' ' << "S: " <<  c2.svf()<< "\t" << "P: " << c2.per() << endl;
    cout << "---------------------------------------" << endl << endl;

    Rectangle r0;
    r0.print();

    Point2D a3, b3(3, 0), c3(3, 4), d3(0, 4);
    vector<Point*> rv = {&a3, &b3, &c3, &d3};
    Rectangle r1("Deeper", rv);
    r1.print();

    Rectangle r2(r0);
    r2.print();

    r2.set_name(r1.get_name());
    r2.set_plenty(r1.get_plenty());
    r2.print();

    cout << r2.get_name() << ' ' << "S: " <<  r2.svf()<< "\t" << "P: " << r2.per() << endl;
    cout << "---------------------------------------" << endl << endl;

    Sphere s0;
    s0.print();

    Point3D p1(1, 1, 1), p2(1, 2, 3);
    vector<Point*> sv = {&p1, &p2};
    Sphere s1("Sir", sv);
    s1.print();

    Sphere s2(s0);
    s2.print();

    s2.set_name(s1.get_name());
    s2.set_plenty(s1.get_plenty());
    s2.print();

    cout << s2.get_name() << ' ' << "V: " <<  s2.svf()<< "\t" << "S: " << s2.per() << endl;
    cout << s0.get_name() << ' ' << "V: " <<  s0.svf()<< "\t" << "S: " << s0.per() << endl;
    cout << "---------------------------------------" << endl << endl;

    Tetrahedron tet0;
    tet0.print();
    cout << tet0.get_name() << ' ' << "V: " <<  tet0.svf()<< "\t" << "S: " << tet0.per() << endl;

    Point3D pt1(0,0,0), pt2(1, 0, 0), pt3(1/2.0, sqrt(3)/2.0, 0), pt4(1/2.0, sqrt(3)/6.0, sqrt(2)/sqrt(6));
    vector<Point*> tetv = {&pt1, &pt2, &pt3, &pt4};
    Tetrahedron tet1("Tetra", tetv);
    tet1.print();

    Tetrahedron tet2(tet0);
    tet2.print();

    tet2.set_name(tet1.get_name());
    tet2.set_plenty(tet1.get_plenty());
    tet2.print();

    cout << tet2.get_name() << ' ' << "V: " <<  tet2.svf()<< "\t" << "S: " << tet2.per() << endl;
    cout << "---------------------------------------" << endl << endl;

    Parallelepiped par0;
    par0.print();
    cout << par0.get_name() << ' ' << "V: " <<  par0.svf()<< "\t" << "S: " << par0.per() << endl;

    Point3D part1(0,0,0), part2(1,0,0), part3(1,2,0), part4(0,2,0),
            part5(0,0,1), part6(1,0,1), part7(1,2,1), part8(0,2,1);

    vector<Point*> parv = {&part1, &part2, &part3, &part4, &part5, &part6, &part7, &part8};
    Parallelepiped par1("Para", parv);
    par1.print();

    Parallelepiped par2(par0);
    par2.print();

    par2.set_name(par1.get_name());
    par2.set_plenty(par1.get_plenty());
    par2.print();

    cout << par2.get_name() << ' ' << "V: " <<  par2.svf()<< "\t" << "S: " << par2.per() << endl;
    cout << "---------------------------------------" << endl << endl;

    return 0;
}

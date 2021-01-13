#include <iostream>
#include <cstdlib>
#include <cmath>
#include <random>
#include <vector>
#include <ctime>


#define NP          1
#define NODES       10
#define NAGG        1
#define NSTEPS      50
#define D           0.5
#define Dt          0.1
#define DIM         3
#define BOXL        128.
#define EPS         1.e-4
#define ATTACH      (2.+EPS)
#define SEPDISTSQ   ATTACH*ATTACH
#define SEED        345
//****************************************
// this program has a Agg class whose functions are used to create a linked list by adding/removing items
// at specific locations


using namespace std;

class Node
{
    public:
        vector<double> pos;
        Node *next;
        Node(vector<double> pos)
        {
            this->pos = pos;
            next = nullptr;
        }
};

class Agg
{

private:
    Node *head;
    Node *tail;
    int size; //size of linked list
    int Nparcl; // number of particles in one node
    std::vector<double>  pos_needed;
public:


    // constructor
    Agg()
    {
        head = nullptr;
        tail = nullptr;
        size = 0;
        Nparcl = 0;
    }

    vector<double> Get_pos() const
    {
        // we can get the private variable
        return pos_needed;

    }

    void Set_pos(vector<double>  copy)
    {
        // setting the private variable for use in main
        pos_needed = copy;
    }

    // insert node at beginning of list
    void headNode(vector<double> pos)
    {
        Node *node = new Node(pos);

        node->pos = pos;
        node->next = head;
        head = node;

        Nparcl = pos.size(); // get number of particles in one node

        size++; // increment size of list
    }

    // insert node at the end of the list
    void tailNode(vector <double > pos)
    {
        Node *node = new Node(pos);

        if (head==nullptr)
        {
            head = node;
            tail = node;
        }
        else
        {
            tail->next = node;
            tail = node;
        }

        Nparcl = pos.size();

        size++;
    }

    // insert node at given location
    void insertNode(int index, vector<double> pos)
    {
        if (index > size+1 || index < 1) return;

        else if (index==1) headNode(pos);

        else if (index==size) tailNode(pos);

        else
        {
            Node *node = new Node(pos);

            Node *current = head;
            Node *previous;

            for(int i=1;i<index;i++)
            {
                previous = current;
                current = current->next;
            }
            previous->next = node;
            node->next = current;

            Nparcl = pos.size();

            size++;
        }
        //Set_pos(pos);
    }

    // remove first item of the list
    void pop()
    {
        if(head!=nullptr)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
            size--;
        }
    }

    // remove last item of list
    void poptail()
    {
        if(head->next==nullptr)
        {
            pop();
        }
        else if(head!=nullptr)
        {
            Node *current = head;
            Node *previous;
            while (current->next!=nullptr)
            {
                previous = current;
                current = current->next;
            }
            tail = previous;
            previous->next = nullptr;
            delete current;

            size--;
        }
    }

    // remove a given node
    void rmNode(int n)
    {
        if(n>size || n<1) return;
        else if(n==1) pop();
        else if(n==size) poptail();

        else if(head!=nullptr)
        {
            Node *current = head;

            Node *previous;

            for(int i=1;i<n;i++)
            {
                previous = current;
                current = current->next;
            }
            previous->next = current->next;
            delete current;
            size--;
        }
    }

    // get size of list
    int getsize()
    {
        return size;
    }

    // get number of particles in each node
    int getNp(int n)
    {
        if (n>getsize()) return -1;
        else return Nparcl;
    }

    // get data in one specific node
    vector<double> getNode(int m,vector<double> pos)
    {
        Node *n = head;
        int count = 1;
        while(n!=nullptr)
        {
            if (count==m)
            {
                return (n->pos);
            }
            else
            {
                n = n->next;
                count++;
            }
        }
        return (n->pos);
    }
    // measure distance squared between aggregates
    double compute_distsq(vector<double> agg1, vector<double> agg2)
    {
        //double distmin = 0.5*BOXL*sqrt(DIM);
        //double distminsq = distmin*distmin;

        double distminsq = 1e4;

        //vector<double> aggbig = (agg1.size()>=agg2.size()) ? agg1 : agg2;
        //vector<double> aggsmall = (agg1.size()<agg2.size()) ? agg1 : agg2;

        //cout << aggbig[0] << endl;
        //cout << aggsmall[0] << endl;
        //cout << "Big is: " << aggbig.size() << endl;
        //cout << "Small is: " << aggsmall.size() << endl;

        const auto begin1 = agg1.begin();
        const auto begin2 = agg2.begin();

        int NROWS_1 = rint(agg1.size()/(DIM*1.));
        int NROWS_2 = rint(agg2.size()/(DIM*1.));

        //cout << ROWS_1 << endl;
        //cout << ROWS_2 << endl;

        int NCOLS = DIM;

        vector<vector<double> > matrix1;
        vector<vector<double> > matrix2;

        int ncols = NCOLS;

        for( std::size_t row = 0 ; row < NROWS_1 ; ++row )
        {
            matrix1.push_back( { begin1 + row*ncols, begin1 + (row+1)*ncols } ) ;
        }
        for( std::size_t row = 0 ; row < NROWS_2 ; ++row )
        {
            matrix2.push_back( { begin2 + row*ncols, begin2 + (row+1)*ncols } ) ;
        }

        for(int i=0;i<NROWS_1;i++)
        {
            for(int j=0;j<NROWS_2;j++)
            {
                double tmp;
                double sum = 0.;
                for (int d=0;d<DIM;d++)
                {
                    tmp = matrix1[i][d] - matrix2[j][d];
                    tmp -=BOXL*rint(tmp/BOXL);
                    //cout << "tmpsq: " << tmp*tmp << endl;

                    sum += tmp*tmp;
                }
                //cout << "Sum: " << sum << endl;
                //cout << "Distminsq: "<< distminsq << endl;
                distminsq = (sum<distminsq) ? sum : distminsq;
            }
        }
        return distminsq;
    }

    // initialize the list making sure aggregates are well-separated at t=0
    void init_list()
    {

        // at initial time each node will contain one particle only

        // initialize first aggregate

        vector<double> row;
        row.resize(DIM);
        for(int d=0;d<DIM;d++)
        {
            double unif = rand()/(RAND_MAX+1.);
            row[d] = (BOXL*(unif-0.5));
        }
        insertNode(1,row);
        //cout << row[0] << endl;
        Set_pos(row);
        //printlist(row);
        // initialize all the other aggregates
        for (int i=2;i<=NODES;i++)
        {
            vector<double> row2;
            row2.resize(DIM);
            bool keep_init = true;
            while(keep_init)
            {
                for(int d=0;d<DIM;d++)
                {
                    double unif = rand()/(RAND_MAX+1.);
                    row2[d] = (BOXL*(unif-0.5));
                }
                double distsq;
                keep_init = false;
                for (int j=1;j<i;j++)
                {
                    vector<double> posnode = getNode(j,Get_pos());

                    double tmp;
                    double sum = 0.;
                    for (int d=0;d<DIM;d++)
                    {
                        tmp = row2[d] - posnode[d];
                        tmp -= BOXL*rint(tmp/BOXL);
                        sum += tmp*tmp;
                    }
                    distsq = sum;
                    if (distsq<=SEPDISTSQ)
                    {
                        keep_init = true;
                        break;
                    }
                }
            }
            //cout << row2[0] << endl;
            insertNode(i,row2);
            Set_pos(row2);
            //printlist(row2);
        }
        //Set_pos(Get_pos());
        return;
    }

    void translate_agg()
    {

        vector<double> pos = Get_pos();
        Node *n = head; // after one step, you gotta travel the list again
        int ncount = 1;
        while(n!=nullptr)
        {
            //for (int i=1;i<=NODES;i++)
            //{
                //double temp = 0.;
                int seed = rand();
                double dx[DIM];
                std::default_random_engine generator(seed);
                std::normal_distribution<double> distribution(0.,1.);
                for (int d=0;d<DIM;d++)
                {
                    dx[d] = sqrt(2.*D*Dt)*distribution(generator);
                }
                vector<double> parcl = getNode(ncount,Get_pos());
                for(int ij=0;ij<parcl.size();ij++)
                {
                    double temp = parcl[ij];
                    //double dx = sqrt(2.*D*Dt)*distribution(generator);
                    //std::cout << "Step is: " << dx[ij%DIM] << endl;
                    temp+=dx[ij%DIM];
                    temp-=BOXL*rint(temp/BOXL);
                    parcl[ij] = temp;
                }
                Set_pos(parcl);
                vector<double>particle = Get_pos();
                n->pos = particle;
                n = n->next; // travel the list
                ncount++;
            //}
            //Set_pos(pos);
        }
        return;
    }


    vector<double> combine_aggs(int p,int q)
    {
        vector<double> agg1 = getNode(p,Get_pos());
        vector<double> agg2 = getNode(q,Get_pos());
        agg1.insert(agg1.end(),agg2.begin(),agg2.end()); // to concatenate vectors

        rmNode(q);
        return agg1;
    }


    // save the list to a file
    void savelist(FILE *fp, vector<double> pos)
    {

        Node *n = head;
        while(n!=nullptr)
        {
            int count = 0;
            for(int j=0;j<n->pos.size();j++)
            {
                n->pos[j];
                fprintf(fp,"%g\t",n->pos[j]);
                count++;
                if(count%DIM==0) fprintf(fp,"\n");
            }
            n = n->next;
            fprintf(fp,"\n"); // for different nodes
        }
    }

    // print list
    void printlist(vector<double> pos)
    {
        Node *n = head;
        //cout << pos[0][0] <<endl;
        while(n!=nullptr)
        {   int count = 0;
            for(int j=0;j<n->pos.size();j++)
            {
                std:: cout << n->pos[j] << " ";
                count++;
                if(count%DIM==0) std::cout << std::endl;
            }
            std::cout <<"Node "<< n << std::endl;
            n = n->next;
        }
        std::cout  <<std::endl;
    }

    // deconstructor for memory cleanup
    ~Agg()
    {
        Node *next;
        while(head != nullptr)
        {
            next = head->next;
            delete head;
            head = next;
        }
    }
};



int main()
{

    time_t start, end;

    time(&start);

    srand(SEED);
    //std::default_random_engine generator(SEED);
    //std::normal_distribution<double> distribution(0.,1.);

    Agg agg; // first instance of the class


    // initialize list
    agg.init_list();

    //agg.printlist(agg.Get_pos());

    cout << agg.getsize() << endl;


    //for (int k=1;k<=NSTEPS;k++)
    while(agg.getsize()>NAGG)
    {
        agg.translate_agg();

        for (int p=1;p<=agg.getsize();p++)
        {
            vector<double> agg1;
            agg1 = agg.getNode(p,agg.Get_pos());
            for (int q=p+1;q<=agg.getsize();q++)
            {
                vector<double> agg2;
                agg2 = agg.getNode(q,agg.Get_pos());
                double dist = agg.compute_distsq(agg1,agg2);
                //cout << "distsq is: " << dist <<endl;
                //cout << "p is: " << p << endl;
                //cout << "q is: " << q << endl;
                if (dist<=ATTACH*ATTACH)
                {
                    //int kk;
                    //cin >> kk;
                    vector<double> agg1 = agg.combine_aggs(p,q);
                    agg.rmNode(p);
                    //agg.rmNode(p);
                    agg.insertNode(p,agg1);
                }
            }
        }
        //agg.printlist(agg.Get_pos());
    }
    //agg.printlist(agg.Get_pos());

    cout << agg.getsize() << endl;

    char filename3[128];
    sprintf(filename3,"pos_%dd_BOXL_%g_NODES_%d_NAGG_%d_Dt_%g.DAT",DIM,BOXL,NODES,NAGG,Dt);
    FILE *fp3 = fopen(filename3,"w");
    agg.savelist(fp3,agg.Get_pos());
    fclose(fp3);

    time(&end);
    
    double time_taken = double(end - start);

    cout << "Execution time is: " << time_taken << " sec" << endl;

    return(0);
}


namespace iquads{

class stage
{
protected:
  string stage_tag_;
  unsigned int code;
};

template < class Tframe, class Tevolver >
class evolve : protected stage
{
public:
  void perform()
  {
    initial = get_initial();
    final   = evolver.evolve( initial );
    final.save();
  }

private:
  vector<Tframe> frames;
  Tevolver evolver;
};

template < class Tsolver, class Tsolution >
class solve : protected stage
{

public:
  void perform()
  {
    solution   = solver.solve( parameters );
    solution.save();
  }

private:
  Tsolution solution;
  Tsolver solver;

};

} // end of namespace iquads

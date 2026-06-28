// ---------------------------------------------------------------------------- -
// A generator of uniformly distributed random numbers
//-----------------------------------------------------------------------------
class IUniformRandomStream
{
public:
    // Sets the seed of the random number generator
    virtual void	SetSeed(int iSeed) = 0;

    // Generates random numbers
    virtual float	RandomFloat(float flMinVal = 0.0f, float flMaxVal = 1.0f) = 0;
    virtual int		RandomInt(int iMinVal, int iMaxVal) = 0;
    virtual float	RandomFloatExp(float flMinVal = 0.0f, float flMaxVal = 1.0f, float flExponent = 1.0f) = 0;
};
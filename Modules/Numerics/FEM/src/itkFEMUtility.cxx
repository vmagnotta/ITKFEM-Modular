/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#include "itkFEMUtility.h"
#include "itkMetaObjectConverterFactory.h"
#include "itkMetaFEMObjectConverter.h"
#include "itkMacro.h"
#include "metaObject.h"
#include "metaFEMObject.h"
#include "itkFEMObjectSpatialObject.h"
#include "itkSpatialObject.h"

namespace itk
{
namespace fem
{
/**
 * Numerical integration (Gauss-Legendre formula).
 * Integrates function f(x) from x=a to x=b in n points.
 */
double GaussIntegrate::Integrate(double ( *f )(double), double a, double b, int n)
{
  /**
   * This subprogram produces the gauss-legendre numerical
   * integral for

   *   b
   * int   f(x)*dx
   *    a
   *
   * The number of nodes n must satisfy
   *    2 <= n <= 20
   * The following data statements contain the gauss-legendre
   * nodes for the interval [-1,1].
   */

  double scale, t, tl, tu, sum;
  int    i, m, ibase;

  /*  Begin integration  */

  scale = ( b - a ) / two;
  if( ( n & 1 ) == 0 )
    {
    m = n / 2;
    ibase = m * m;
    sum = zero;
    }
  else
    {
    m = ( n - 1 ) / 2;
    ibase = ( n * n - 1 ) / 4;
    sum = w[ibase + m] * ( *f )( ( a + b ) / two );
    }
  for( i = 1; i <= m; i++ )
    {
    t = z[ibase + i - 1];
    tl = ( a * ( one + t ) + ( one - t ) * b ) / two;
    tu = ( a * ( one - t ) + ( one + t ) * b ) / two;
    sum = sum + w[ibase + i - 1] * ( ( *f )( tl )  + ( *f )( tu ) );
    }

  return scale * sum;
}

const double GaussIntegrate::zero = 0.0;
const double GaussIntegrate::one = 1.0;
const double GaussIntegrate::two = 2.0;
const double GaussIntegrate::z[110] =
  {
  0.0, 0.577350269189626, 0.774596669241483, 0.0,
  0.861136311594053, 0.339981043584856, 0.906179845938664,
  0.538469310105683, 0.0, 0.932469514203152,
  0.661209386466265, 0.238619186083197, 0.949107912342759,
  0.741531185599394, 0.405845151377397, 0.0,
  0.960289856497536, 0.796666477413627, 0.525532409916329,
  0.183434642495650, 0.968160239507626, 0.836031107326636,
  0.613371432700590, 0.324253423403809, 0.0,
  0.973906528517172, 0.865063366688985, 0.679409568299024,
  0.433395394129247, 0.148874338981631, 0.978228658146057,
  0.887062599768095, 0.730152005574049, 0.519096129206812,
  0.269543155952345, 0.0, 0.981560634246719,
  0.904117256370475, 0.769902674194305, 0.587317954286617,
  0.367831498998180, 0.125233408511469, 0.984183054718588,
  0.917598399222978, 0.801578090733310, 0.642349339440340,
  0.448492751036447, 0.230458315955135, 0.0,
  0.986283808696812, 0.928434883663574, 0.827201315069765,
  0.687292904811685, 0.515248636358154, 0.319112368927890,
  0.108054948707344, 0.987992518020485, 0.937273392400706,
  0.848206583410427, 0.724417731360170, 0.570972172608539,
  0.394151347077563, 0.201194093997435, 0.0,
  0.989400934991650, 0.944575023073233, 0.865631202387832,
  0.755404408355003, 0.617876244402644, 0.458016777657227,
  0.281603550779259, 0.0950125098376374, 0.990575475314417,
  0.950675521768768, 0.880239153726986, 0.781514003896801,
  0.657671159216691, 0.512690537086477, 0.351231763453876,
  0.178484181495848, 0.0, 0.991565168420931,
  0.955823949571398, 0.892602466497556, 0.803704958972523,
  0.691687043060353, 0.559770831073948, 0.411751161462843,
  0.251886225691506, 0.0847750130417353, 0.992406843843584,
  0.960208152134830, 0.903155903614818, 0.822714656537143,
  0.720966177335229, 0.600545304661681, 0.464570741375961,
  0.316564099963630, 0.160358645640225, 0.0,
  0.993128599185095, 0.963971927277914, 0.912234428251326,
  0.839116971822219, 0.746331906460151, 0.636053680726515,
  0.510867001950827, 0.373706088715420, 0.227785851141645,
  0.0765265211334973
  };

const double GaussIntegrate::w[110] =
  {
  0.0, 1.0, 0.555555555555556, 0.888888888888889,
  0.347854845137454, 0.652145154862546, 0.236926885056189,
  0.478628670499366, 0.568888888888889, 0.171324492379170,
  0.360761573048139, 0.467913934572691, 0.129484966168870,
  0.279705391489277, 0.381830050505119, 0.417959183673469,
  0.101228536290376, 0.222381034453374, 0.313706645877887,
  0.362683783378362, 0.0812743883615744, 0.180648160694857,
  0.260610696402935, 0.312347077040003, 0.330239355001260,
  0.0666713443086881, 0.149451349150581, 0.219086362515982,
  0.269266719309996, 0.295524224714753, 0.0556685671161737,
  0.125580369464905, 0.186290210927734, 0.233193764591990,
  0.262804544510247, 0.272925086777901, 0.0471753363865118,
  0.106939325995318, 0.160078328543346, 0.203167426723066,
  0.233492536538355, 0.249147045813403, 0.0404840047653159,
  0.0921214998377284, 0.138873510219787, 0.178145980761946,
  0.207816047536889, 0.226283180262897, 0.232551553230874,
  0.0351194603317519, 0.0801580871597602, 0.121518570687903,
  0.157203167158194, 0.185538397477938, 0.205198463721296,
  0.215263853463158, 0.0307532419961173, 0.0703660474881081,
  0.107159220467172, 0.139570677926154, 0.166269205816994,
  0.186161000015562, 0.198431485327112, 0.202578241925561,
  0.0271524594117541, 0.0622535239386478, 0.0951585116824928,
  0.124628971255534, 0.149595988816577, 0.169156519395003,
  0.182603415044924, 0.189450610455068, 0.0241483028685479,
  0.0554595293739872, 0.0850361483171792, 0.111883847193404,
  0.135136368468525, 0.154045761076810, 0.168004102156450,
  0.176562705366993, 0.179446470356207, 0.0216160135264833,
  0.0497145488949698, 0.0764257302548891, 0.100942044106287,
  0.122555206711478, 0.140642914670651, 0.154684675126265,
  0.164276483745833, 0.169142382963144, 0.0194617882297265,
  0.0448142267656996, 0.0690445427376412, 0.0914900216224500,
  0.111566645547334, 0.128753962539336, 0.142606702173607,
  0.152766042065860, 0.158968843393954, 0.161054449848784,
  0.0176140071391521, 0.0406014298003869, 0.0626720483341091,
  0.0832767415767047, 0.101930119817240, 0.118194531961518,
  0.131688638449177, 0.142096109318382, 0.149172986472604,
  0.152753387130726
  };

template <unsigned NDimension>
MetaObject *InternalConvertSpatialObjectFEMMetaObject(void *objToConvert)
{
  typedef SpatialObject<NDimension> SpatialObjectType;

  SpatialObjectType *so =
    reinterpret_cast<SpatialObjectType *>(objToConvert);

  typedef itk::FEMObjectSpatialObject<NDimension> FEMSOType;
  FEMSOType * femSO = dynamic_cast<FEMSOType *>(so);
  if(femSO != 0)
    {
    typedef itk::fem::FEMObject<NDimension> FEMObjectType;

    MetaFEMObjectConverter<NDimension> converter;
    MetaFEMObject            *fem =
      converter.FEMObjectSpatialObjectToMetaFEMObject(femSO);
    if(so->GetParent())
      {
      fem->ParentID(so->GetParent()->GetId());
      }
    fem->Name(so->GetProperty()->GetName().c_str());
    return fem;
    }
  return 0;
}

MetaObject *
ConvertFEMMetaObject(void *objToConvert)
{
  MetaObject *rval;
  if((rval = InternalConvertSpatialObjectFEMMetaObject<2>(objToConvert)) == 0 &&
     (rval = InternalConvertSpatialObjectFEMMetaObject<3>(objToConvert)) == 0
     )
    {
    itkGenericExceptionMacro(<< "Can't convert MetaObject to FEMMetaObject");
    }
  return rval;
}

}  //end namespace fem

}  // end namespace itk

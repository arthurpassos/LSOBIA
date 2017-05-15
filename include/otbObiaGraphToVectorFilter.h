#ifndef otbObiaGraphToVectorFilter_h
#define otbObiaGraphToVectorFilter_h

#include "itkProcessObject.h"
#include <otbOGRDataSourceWrapper.h>

namespace otb
{
namespace obia
{

/** \class GraphToGraphFilter
 *	\brief Base class for all process objects that requires one input graph
 	and that provides one output graph data.
 *
 */
template< typename TInputGraph>
class ITK_EXPORT GraphToVectorFilter : public itk::ProcessObject
{

public:

	/** Standard class alias */
	using Self         = GraphToVectorFilter;
	using Superclass   = itk::ProcessObject;
	using Pointer      = itk::SmartPointer<Self>;
	using ConstPointer = itk::SmartPointer< const Self >;

	/** Run-time type information (and related methods). */
  	itkNewMacro(Self);

  	/** Some convenient typedefs. */
  	using InputGraphType         = TInputGraph;
  	using InputGraphPointer      = typename InputGraphType::Pointer;
  	using InputGraphConstPointer = typename InputGraphType::ConstPointer;

  	using OTBFeature			 = otb::ogr::Feature;
  	using OTBLayer			     = otb::ogr::Layer;

  	/** Return the name of the class. */
	itkTypeMacro(GraphToVectorFilter, ProcessObject);

	  /** Definition of the input image */
	using OGRDataSourceType = otb::ogr::DataSource;
	using OGRDataSourcePointerType = OGRDataSourceType::Pointer;
	using OGRLayerType = OTBLayer;
	using DataObjectPointerArraySizeType =  itk::ProcessObject::DataObjectPointerArraySizeType;


	/** Set/Get the input graph of this process object.  */
	using Superclass::SetInput;
	virtual void SetInput(const TInputGraph *input);
	virtual const TInputGraph * GetInput(void);

	/** Set the Field Name in which labels will be written. (default is "DN")
	* A field "FieldName" of type integer is created in the output memory layer.
	*/
	itkSetMacro(FieldName, std::string);
	/**
	* Return the Field name in which labels have been written.
	*/
	itkGetMacro(FieldName, std::string);

	/**
	* Set the value of 8-connected neighborhood option used in \c GDALPolygonize
	*/
	itkSetMacro(Use8Connected, bool);
	/**
	* Get the value of 8-connected neighborhood option used in \c GDALPolygonize
	*/
	itkGetMacro(Use8Connected, bool);

	/**
	* Get the output \c ogr::DataSource which is a "memory" datasource.
	*/
	const OGRDataSourceType * GetOutput();

	protected:

	GraphToVectorFilter();
	~GraphToVectorFilter() ITK_OVERRIDE {}

	void GenerateInputRequestedRegion() ITK_OVERRIDE;

	/** Generate Data method*/
	void GenerateData() ITK_OVERRIDE;

	/** DataObject pointer */
	typedef itk::DataObject::Pointer DataObjectPointer;

	DataObjectPointer MakeOutput(DataObjectPointerArraySizeType idx) ITK_OVERRIDE;
	using Superclass::MakeOutput;

	/**GDAL Method*/
	GDALDriver* initializeGDALDriver(std::string driverName);

	//Create a field
	void CreateNewField(OTBLayer poLayer, std::string fieldName, OGRFieldType fieldType);

	//Self intersecting points
	std::vector<OGRPoint> GetSelfIntersectingPoints(OGRPolygon* ogrPolygon);

	//Clean Layer
	void CleanOGRLayer(OTBLayer poLayer, OTBLayer& poLayer_cleaned);

	//Clean Geometry
	OGRPolygon* CleanSelfIntersectingPolygon(OGRPolygon* ogrPolygon);

	//Create new Geometry
	OGRPolygon* CreateSubGeomtry(OGRPointIterator* pIt, OGRPoint selfIntersectingPoint);

	//Self intetrsecting
	bool IsSelfIntersecting(OGRPoint p, std::vector<OGRPoint> listSelf);

	//Create feature for all polygons
	void CreateAllFeatures(OTBLayer& poLayer);

	//Update the feature like adjacent polygons, etc ...
	void UpdateFeatureFields(OGRFeature* curFeature);

	//Add Feature for a given geometry
	void SetNewFields(OGRFeature* curFeature);

	//Write into a file
	void WriteFile(std::string filepath);

	private:

	GraphToVectorFilter(const Self &);  //purposely not implemented
	void operator =(const Self&);      //purposely not implemented

	std::string m_FieldName;
	bool m_Use8Connected;
	InputGraphPointer m_graph;


};

} // end of namespace obia
} // end of namespace otb

#include "otbObiaGraphToVectorFilter.txx"
#endif

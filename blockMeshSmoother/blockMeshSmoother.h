#ifndef BLOCKMESHSMOOTHER_H
#define BLOCKMESHSMOOTHER_H

#include "blockMesh.H"

#include <set>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
             Class blockMeshSmoother Declaration
\*---------------------------------------------------------------------------*/

class blockMeshSmoother
{
    // Private data


        // Pointer to blockMesh
        blockMesh *blockMeshPtr_;

        // Dictionary
        dictionary dict_;

        // List of cell linked to points
        labelListList pointCells_;

        // list of points for each cell
        // FIXME change with direct function "pointsLabels"
        labelListList cellPoints_;

        // cell linked to points
        List<std::set<label> > pointCellsS_;

        // cell linked to cells
        List<std::set<label> > cellNeighbors_;

        // Sum of cell quality for each pt
        scalarList sumCellQuality_;

        // Set of mobiles points
        std::set<label> mobilPoints_;

        // List of cell quality
        scalarList cellQuality_;

    // Private member functions

        //- Mean ratio
        void meshMeanRatio(scalar &min, scalar &avg);

        // AddTransformedElementNodesAndWeights
        pointField addTransformedElementNodesAndWeights
        (
            scalarList &wj,
            std::set<label> &tp,
            const scalar &targetQual,
            const scalar &eTP
        );

        std::set<label> getTransformedAndFreePoints(std::set<label> &tp);

        void addUntransformedElementNodesAndWeights
        (
            pointField &pi,
            scalarList &wj,
            std::set<label> &tn,
            const scalar &targetQual
        );

        void computeNewNodes
        (
            pointField &pi,
            scalarList &wj,
            std::set<label> &tn
        );

        pointField iterativeNodeRelaxation
        (
            pointField &pi,
            std::set<label> &tn,
            const scalarList &rT
        );

public:

    //- Runtime type information
//    TypeName("blockMeshSmoother");


    // Constructors

        //- Construct from blockMesh and dictionary
        blockMeshSmoother(blockMesh &block, dictionary &smootherDict);

    // Member functions

        //- Start smoothing
        void smoothing();

};

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // BLOCKMESHSMOOTHER_H

// ************************************************************************* //

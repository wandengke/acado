/*
 *    This file is part of ACADO Toolkit.
 *
 *    ACADO Toolkit -- A Toolkit for Automatic Control and Dynamic Optimization.
 *    Copyright (C) 2008-2009 by Boris Houska and Hans Joachim Ferreau, K.U.Leuven.
 *    Developed within the Optimization in Engineering Center (OPTEC) under
 *    supervision of Moritz Diehl. All rights reserved.
 *
 *    ACADO Toolkit is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License as published by the Free Software Foundation; either
 *    version 3 of the License, or (at your option) any later version.
 *
 *    ACADO Toolkit is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with ACADO Toolkit; if not, write to the Free Software
 *    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */



/**
 *    \file src/code_generation/linear_solver_export.cpp
 *    \author Rien Quirynen
 *    \date 2012
 */

#include <acado/code_generation/linear_solvers/linear_solver_export.hpp>


BEGIN_NAMESPACE_ACADO


//
// PUBLIC MEMBER FUNCTIONS:
//

ExportLinearSolver::ExportLinearSolver( UserInteraction* _userInteraction,
									const String& _commonHeaderName
									) : ExportAlgorithm( _userInteraction,_commonHeaderName )
{
	REUSE = BT_TRUE;		// DEFAULT value
	UNROLLING = BT_FALSE;	// DEFAULT value
	dim = 0;

	determinant = ExportVariable( "det", 1, 1, REAL, ACADO_LOCAL, BT_TRUE );
}


ExportLinearSolver::ExportLinearSolver( const ExportLinearSolver& arg ) : ExportAlgorithm( arg )
{
	init( arg.dim, arg.REUSE, arg.UNROLLING );
}


ExportLinearSolver::~ExportLinearSolver( )
{
}


ExportLinearSolver& ExportLinearSolver::operator=( const ExportLinearSolver& arg )
{
	if( this != &arg )
	{
		ExportAlgorithm::operator=( arg );
		init( arg.dim, arg.REUSE, arg.UNROLLING );
	}

	return *this;
}


returnValue ExportLinearSolver::init(	const uint newDim,
										const BooleanType& reuse,
										const BooleanType& unrolling
										)
{
	return init( newDim, reuse, unrolling, String( "dim" ) << String( newDim ) << "_" );
}


returnValue ExportLinearSolver::init(	const uint newDim,
										const BooleanType& reuse,
										const BooleanType& unrolling,
										const String& newId
										)
{
	REUSE = reuse;
	UNROLLING = unrolling;
	dim = newDim;
	identifier = newId;
	setup();
	
	return SUCCESSFUL_RETURN;
}



uint ExportLinearSolver::getDim() const {
	
	return dim;
}


BooleanType ExportLinearSolver::getReuse() const {
	
	return REUSE;
}


returnValue ExportLinearSolver::setReuse( const BooleanType& reuse ) {
	
	REUSE = reuse;
	
	return SUCCESSFUL_RETURN;
} 


BooleanType ExportLinearSolver::getUnrolling() const {
	
	return UNROLLING;
}


returnValue ExportLinearSolver::setUnrolling( const BooleanType& unrolling ) {
	
	UNROLLING = unrolling;
	
	return SUCCESSFUL_RETURN;
} 


const String ExportLinearSolver::getNameSolveFunction() {
	
	return String( "solve_" ) << identifier << "system";
}


const String ExportLinearSolver::getNameSolveReuseFunction() {
	
	return String( "solve_" ) << identifier << "system_reuse";
}


//
// PROTECTED MEMBER FUNCTIONS:
//



CLOSE_NAMESPACE_ACADO

// end of file.

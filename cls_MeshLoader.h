#include <iostream>
#include <iterator>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <exception>
#include "Types.h"

class cls_MeshLoader
{
protected:
	class BadFileFormatException : public std::exception {
    std::string Error;
public:
    BadFileFormatException() {
        Error.assign("Unknown or unsupported file format!");
    }
    explicit BadFileFormatException(const std::string& file_format) {
        Error.assign("File format \"" + file_format + "\" is not supported!");
    }
    const char* what() const override {
        return Error.c_str();
    }
};

class NoFileFoundException : public std::exception {
    std::string error;
public:
    NoFileFoundException() {
        error.assign("Cannot open file! Probably it does not exist!");
    }
    explicit NoFileFoundException(const std::string& file) {
        error.assign("Cannot open file: \"" + file + "\"! Probably it does not exist!");
    }
    const char* what() const override {
        return error.c_str();
    }
};
    unsigned m_Dim;
    unsigned m_N_NodesinFE;
    unsigned m_N_NodesinSFE;
    std::vector<Node> m_Nodes;
    std::vector<FiniteElement> m_FEs;
    std::vector<SurfaceFiniteElement> m_SFEs;
public:
	virtual void LoadMesh(const std::string& fileName) = 0;
    std::vector<Node> getNodes() const;
    std::vector<FiniteElement> getFiniteElements() const;
    std::vector<SurfaceFiniteElement> getSurfaceFiniteElements() const;
    std::vector<FiniteElement> findFE_byNodes(unsigned p_ID1, unsigned p_ID2, unsigned p_ID3) const;
    std::vector<FiniteElement> findFE_byEdge(unsigned p_ID1, unsigned p_ID2) const;
    std::vector<Node> getSFNs_byIDSurface(int p_IDSurface) const;
    std::vector<FiniteElement> getFEs_byTypeID(int p_IDType) const;
    std::vector<SurfaceFiniteElement> getSFEs_byIDSurface(int p_ID) const;
	std::vector<std::vector<Node>> Get_Nodes_Neighbors() const;
    void Transform_to_Quadratic();
};

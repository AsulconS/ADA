/********************************************************************************
 *                                                                              *
 * Copyright (c) 2020 Adrian Bedregal                                           *
 *                                                                              *
 * This software is provided 'as-is', without any express or implied            *
 * warranty. In no event will the authors be held liable for any damages        *
 * arising from the use of this software.                                       *
 *                                                                              *
 * Permission is granted to anyone to use this software for any purpose,        *
 * including commercial applications, and to alter it and redistribute it       *
 * freely, subject to the following restrictions:                               *
 *                                                                              *
 * 1. The origin of this software must not be misrepresented; you must not      *
 *    claim that you wrote the original software. If you use this software      *
 *    in a product, an acknowledgment in the product documentation would be     *
 *    appreciated but is not required.                                          *
 * 2. Altered source versions must be plainly marked as such, and must not be   *
 *    misrepresented as being the original software.                            *
 * 3. This notice may not be removed or altered from any source distribution.   *
 *                                                                              *
 ********************************************************************************/

#ifndef COLORED_SPHERE_HPP
#define COLORED_SPHERE_HPP

#include <HSGIL/hsgil.hpp>
#include <random>

class ColoredSphere : public gil::Mesh
{
public:
    ColoredSphere(const float t_radius, const gil::uint32 t_ringCount = 18, const gil::uint32 t_segmentCount = 36);
    virtual ~ColoredSphere();

    void shuffle(gil::RenderingWindow& renderingWindow, const gil::Shader& shader);
    void sortWithMergeSort(gil::RenderingWindow& renderingWindow, const gil::Shader& shader);

    gil::uint32 getNumberOfVertices();

    virtual void draw(const gil::Shader& shader) override;

protected:
    virtual void generate() override;

private:
    float m_radius;
    gil::uint32 m_ringCount;
    gil::uint32 m_segmentCount;

    gil::Vector<float> m_sVertexData;
    gil::Vector<gil::uint32> m_values;

    void generateBallVerticesAndIndices();

    void setColorAtIndex(const gil::uint32 i, const gil::Vec3f& col);
    void swapWithIndices(const gil::uint32 i1, const gil::uint32 i2);

    void merge(gil::RenderingWindow& renderingWindow, const gil::Shader& shader, gil::uint32* aux, gil::Vec3f* auxColors, int p, int q, int r);
    void mergeSortInternal(gil::RenderingWindow& renderingWindow, const gil::Shader& shader, gil::uint32* aux, gil::Vec3f* auxColors, int p, int r);
};

#endif // COLORED_SPHERE_HPP

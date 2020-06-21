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

#include <coloredSphere.hpp>

ColoredSphere::ColoredSphere(const float t_radius, const gil::uint32 t_ringCount, const gil::uint32 t_segmentCount)
    : gil::Mesh      {},
      m_radius       {t_radius},
      m_ringCount    {t_ringCount},
      m_segmentCount {t_segmentCount}
{
    generateBallVerticesAndIndices();
    generate();
}

ColoredSphere::~ColoredSphere()
{
}

void ColoredSphere::shuffle(gil::RenderingWindow& renderingWindow, const gil::Shader& shader)
{
    shader.use();
    int size = getNumberOfVertices();

    gil::Vec3f tempColor {};
    gil::uint32 tempValue {};

    std::random_device rd;
    std::mt19937_64 mt(rd());
    std::uniform_int_distribution<int> dist(0, size);

    int ri {};
    for(int i = 0; i < size; ++i)
    {
        ri = dist(mt);
        swapWithIndices(i, ri);

        //glClearColor(0.125f, 0.125f, 0.125f, 1.0f);
        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //draw(shader);
        //renderingWindow.swapBuffers();

        //Sleep(0.5f);
    }
}

void ColoredSphere::sortWithMergeSort(gil::RenderingWindow& renderingWindow, const gil::Shader& shader)
{
    gil::uint32* aux = new gil::uint32[m_values.size()];
    gil::Vec3f* auxColors = new gil::Vec3f[m_values.size()];
    mergeSortInternal(renderingWindow, shader, aux, auxColors, 0, m_values.size() - 1);
    delete[] aux;
    delete[] auxColors;
}

void ColoredSphere::draw(const gil::Shader& shader)
{
    shader.use();
    glBindVertexArray(m_VAO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, m_sVertexData.size() * sizeof(float), m_sVertexData.data());
        glDrawElements(GL_TRIANGLES, (gil::uint32)m_indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);
}

gil::uint32 ColoredSphere::getNumberOfVertices()
{
    return m_values.size();
}

void ColoredSphere::generate()
{
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, m_sVertexData.size() * sizeof(float), m_sVertexData.data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(gil::uint32), m_indices.data(), GL_STATIC_DRAW);

    // Position Attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color Attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Normal Attribute
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void ColoredSphere::generateBallVerticesAndIndices()
{
    float x, y, z, zx;
    float nx, ny, nz;
    float radiusInvLen = 1.0f / m_radius;

    float sectorStep = 2 * gil::constants::PI / m_segmentCount;
    float stackStep = gil::constants::PI / m_ringCount;
    float sectorAngle, stackAngle;

    for(gil::uint32 i = 0; i <= m_ringCount; ++i)
    {
        stackAngle = gil::constants::PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
        zx = m_radius * cosf(stackAngle);              // r * cos(u)
        y  = m_radius * sinf(stackAngle);              // r * sin(u)

        for(gil::uint32 j = 0; j < m_segmentCount; ++j)
        {
            sectorAngle = j * sectorStep;           // starting from 0 to 2pi

            // value for this vertex
            m_values.push_back(i * m_segmentCount + j);

            // vertex position (x, y, z)
            z = zx * cosf(sectorAngle);             // r * cos(u) * cos(v)
            x = zx * sinf(sectorAngle);             // r * cos(u) * sin(v)
            m_vertexData.push_back(x);
            m_vertexData.push_back(y);
            m_vertexData.push_back(z);
            m_sVertexData.push_back(x);
            m_sVertexData.push_back(y);
            m_sVertexData.push_back(z);

            float rIntensity {0.0f};
            float gIntensity {0.0f};
            float bIntensity {0.0f};
            gil::uint32 colorPortion = static_cast<gil::uint32>(m_ringCount / 3u);
            if(gil::isBetween(i, 0u, colorPortion))
            {
                rIntensity = 1.0f - (static_cast<float>(i) / static_cast<float>(colorPortion));
                gIntensity = static_cast<float>(i) / static_cast<float>(colorPortion);
            }
            else if(gil::isBetween(i, colorPortion, 2u * colorPortion))
            {
                gIntensity = 1.0f - (static_cast<float>(i - colorPortion) / static_cast<float>(colorPortion));
                bIntensity = static_cast<float>(i - colorPortion) / static_cast<float>(colorPortion);
            }
            else
            {
                bIntensity = 1.0f - (static_cast<float>(i - 2u * colorPortion) / static_cast<float>(colorPortion));
                rIntensity = static_cast<float>(i - 2u * colorPortion) / static_cast<float>(colorPortion);
            }
            // vertex color
            m_vertexData.push_back(rIntensity);
            m_vertexData.push_back(gIntensity);
            m_vertexData.push_back(bIntensity);
            m_sVertexData.push_back(rIntensity);
            m_sVertexData.push_back(gIntensity);
            m_sVertexData.push_back(bIntensity);

            // normalized vertex normal (nx, ny, nz)
            nx = x * radiusInvLen;
            ny = y * radiusInvLen;
            nz = z * radiusInvLen;
            m_vertexData.push_back(nx);
            m_vertexData.push_back(ny);
            m_vertexData.push_back(nz);
            m_sVertexData.push_back(nx);
            m_sVertexData.push_back(ny);
            m_sVertexData.push_back(nz);
        }
    }

    gil::uint32 k1, k2;
    for(gil::uint32 i = 0; i < m_ringCount; ++i)
    {
        k1 = i * m_segmentCount;       // beginning of current stack
        k2 = k1 + m_segmentCount;      // beginning of next stack

        for(gil::uint32 j = 0; j < m_segmentCount; ++j)
        {
            // 2 triangles per sector excluding first and last stacks
            // k1 => k2 => k1+1
            if(i != 0)
            {
                m_indices.push_back(k1 + j);
                m_indices.push_back(k2 + j);
                m_indices.push_back(k1 + j + 1);
            }
            else if(j == m_segmentCount - 1)
            {
                m_indices.push_back(k1 + j);
                m_indices.push_back(k2 + j);
                m_indices.push_back(k2 + j + 1);
            }

            // k1+1 => k2 => k2+1
            if(i != (m_ringCount - 1))
            {
                m_indices.push_back(k1 + j + 1);
                m_indices.push_back(k2 + j);
                m_indices.push_back(k2 + j + 1);
            }
        }
    }
}

void ColoredSphere::setColorAtIndex(const gil::uint32 i, const gil::Vec3f& col)
{
    m_sVertexData[9 * i + 3] = col.x;
    m_sVertexData[9 * i + 4] = col.y;
    m_sVertexData[9 * i + 5] = col.z;

    float rDiff = gil::absolute(m_vertexData[9 * i + 3] - m_sVertexData[9 * i + 3]);
    float gDiff = gil::absolute(m_vertexData[9 * i + 4] - m_sVertexData[9 * i + 4]);
    float bDiff = gil::absolute(m_vertexData[9 * i + 5] - m_sVertexData[9 * i + 5]);

    m_sVertexData[9 * i + 0] = m_vertexData[9 * i + 0] + (0.16f * rDiff);
    m_sVertexData[9 * i + 1] = m_vertexData[9 * i + 1] + (0.16f * gDiff);
    m_sVertexData[9 * i + 2] = m_vertexData[9 * i + 2] + (0.16f * bDiff);
}

void ColoredSphere::swapWithIndices(const gil::uint32 i1, const gil::uint32 i2)
{
    gil::Vec3f tempColor =
    {
        m_sVertexData[9 * i1 + 3],
        m_sVertexData[9 * i1 + 4],
        m_sVertexData[9 * i1 + 5]
    };
    gil::uint32 tempValue = m_values[i1];

    gil::Vec3f i2Color =
    {
        m_sVertexData[9 * i2 + 3],
        m_sVertexData[9 * i2 + 4],
        m_sVertexData[9 * i2 + 5]
    };
    m_values[i1] = m_values[i2];
    setColorAtIndex(i1, i2Color);

    m_values[i2] = tempValue;
    setColorAtIndex(i2, tempColor);
}

void ColoredSphere::merge(gil::RenderingWindow& renderingWindow, const gil::Shader& shader, gil::uint32* aux, gil::Vec3f* auxColors, int p, int q, int r)
{
    int i {};
    int j {};

    for(i = p; i <= q; ++i)
    {
        auxColors[i] =
        {
            m_sVertexData[9 * i + 3],
            m_sVertexData[9 * i + 4],
            m_sVertexData[9 * i + 5]
        };
        aux[i] = m_values.data()[i];
    }
    for(j = q + 1; j <= r; ++j)
    {
        auxColors[(q + 1) + (r - j)] =
        {
            m_sVertexData[9 * j + 3],
            m_sVertexData[9 * j + 4],
            m_sVertexData[9 * j + 5]
        };
        aux[(q + 1) + (r - j)] = m_values.data()[j];
    }
    i = p;
    j = r;

    for(int k = p; k <= r; ++k)
    {
        if(aux[i] <= aux[j])
        {
            m_values.data()[k] = aux[i];
            setColorAtIndex(k, auxColors[i]);
            //glClearColor(0.125f, 0.125f, 0.125f, 1.0f);
            //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            //draw(shader);
            //renderingWindow.swapBuffers();

            //Sleep(0.5f);
            ++i;
        }
        else
        {
            m_values.data()[k] = aux[j];
            setColorAtIndex(k, auxColors[j]);
            //glClearColor(0.125f, 0.125f, 0.125f, 1.0f);
            //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            //draw(shader);
            //renderingWindow.swapBuffers();

            //Sleep(0.5f);
            --j;
        }
    }
}

void ColoredSphere::mergeSortInternal(gil::RenderingWindow& renderingWindow, const gil::Shader& shader, gil::uint32* aux, gil::Vec3f* auxColors, int p, int r)
{
    if(p < r)
    {
        int q = (p + r) / 2;
        mergeSortInternal(renderingWindow, shader, aux, auxColors, p, q);
        mergeSortInternal(renderingWindow, shader, aux, auxColors, q + 1, r);
        merge(renderingWindow, shader, aux, auxColors, p, q, r);
    }
}

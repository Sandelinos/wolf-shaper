#ifndef SPOONIE_GRAPH_WIDGET_HPP_INCLUDED
#define SPOONIE_GRAPH_WIDGET_HPP_INCLUDED

#include "ObjectPool.hpp"
#include "DistrhoUI.hpp"
#include "Graph.hpp"
#include "GraphNodesLayer.hpp"

START_NAMESPACE_DISTRHO

class GraphVertex;
class GraphTensionHandle;
class GraphNode;
class WaveShaperUI;

class GraphWidget : public NanoWidget,
                    public IdleCallback
{
  friend class GraphNode;
  friend class GraphVertex;
  friend class GraphTensionHandle;
  friend class GraphNodesLayer;

public:
  GraphWidget(WaveShaperUI *ui, Window &parent);
  ~GraphWidget();

  /**
   * Recreate the graph according to a saved state.
   */
  void rebuildFromString(const char *serializedGraph);

  /**
   * Reset the graph back into its default state.
   */
  void reset();

protected:
  /**
   * DPF stuff
   */
  void onNanoDisplay() override;
  bool onScroll(const ScrollEvent &ev) override;
  bool onMouse(const MouseEvent &ev) override;
  bool onMotion(const MotionEvent &ev) override;
  void idleCallback() override;

  /**
   * Unused.
   */
  void updateAnimations();

  /**
   * Flip the Y axis so that the origin of the graph is located at the bottom-left corner.
   */
  void flipYAxis();

  /**
   * Draw the grid of the graph.
   */
  void drawGrid();

  /**
   * Divide the cells on the grid into more cells.
   */
  void drawSubGrid();

  /**
   * Draw the background of the graph.
   */
  void drawBackground();

  /**
   * Draw the line on the graph according to the current state of the plugin.
   */
  void drawGraphLine(float lineWidth, Color color);

  /**
   * Draw lines to help the user align the currently grabbed node.
   */
  void drawAlignmentLines();

  /**
   * Draw a vertical line to indicate the input volume on the graph.
   */
  void drawInputIndicator();

  /**
   * Insert a new vertex into the graph at a specified location and return a pointer to it. 
   * The position is in absolute coordinates.
   */
  GraphVertex *insertVertex(const DGL::Point<int> pos);

  /**
   * Remove a vertex at the specified index.
   */
  void removeVertex(const int index);

  /**
   * Mouse handling stuff
   */
  bool leftClick(const MouseEvent &ev);
  bool middleClick(const MouseEvent &ev);
  bool rightClick(const MouseEvent &ev);

private:
  WaveShaperUI *ui;

  /**
   * Initialize the left and right vertices in the graph.
   */
  void initializeDefaultVertices();

  /**
   * Reset the object pool that contains the vertices of the graph.
   */
  void resetVerticesPool();

  /**
   * The data structure that contains the graph. Kept synchronized with the dsp side of the plugin.
   */
  spoonie::Graph lineEditor;

  /**
   * The widget on which the nodes are rendered.
   */
  GraphNodesLayer graphNodesLayer;

  /**
   * Contains the vertex widgets used in the graph.
   */
  GraphVertex *graphVertices[spoonie::maxVertices];

  /**
   * Object pool that holds the vertex widgets.
   */
  spoonie::ObjectPool<GraphVertex> graphVerticesPool;

  /**
   * The graph element which currently has mouse focus.
   */
  GraphNode *focusedElement;

  /**
   * Determine if a mouse button is down.
   */
  bool mouseLeftDown;
  bool mouseRightDown;

  /**
   * The radius size of the vertices in the graph.
   */
  const float absoluteVertexSize = 7.0f;

  /**
   * Define the space around the grid of the graph.
   */
  const int marginTop = 36;
  const int marginLeft = 48;
  const int marginRight = 48;
  const int marginBottom = 84;

  float maxInput;

  DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GraphWidget)
};

END_NAMESPACE_DISTRHO

#endif
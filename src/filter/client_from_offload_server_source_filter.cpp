#include "client_from_offload_server_source_filter.hpp"
#include "grid.hpp"
#include "field.hpp"
#include "file.hpp"
#include "exception.hpp"
#include "calendar_util.hpp"
#include "context.hpp"
#include "event_client.hpp"
#include "timer.hpp"
#include "tracer.hpp"
#include <limits> 
#include <vector> 
#include "workflow_graph.hpp"

namespace xios
{
  CClientFromOffloadServerSourceFilter::CClientFromOffloadServerSourceFilter(CGarbageCollector& gc, CField* field)
    : COutputPin(gc, true)
  {
    CContext* context = getContext();
    field_ = field ;
    grid_= field->getSentGrid();
    client_ = field->getOffloadFunction()->getContextClient();
  }

  void CClientFromOffloadServerSourceFilter::streamData(CEventServer& event)
  {
    CContext* context = getContext();
    int record ;
    for (auto& subEvent : event.subEvents) (*subEvent.buffer) >> record  ;

        
    CDataPacketPtr packet(new CDataPacket);
    packet->date = context->getCalendar()->getCurrentDate();
    packet->timestamp = packet->date ;

    CContextClient* client = event.getContextServer()->getAssociatedClient() ;
    grid_->getClientFromServerConnector(client)->transfer(event, packet->data) ; // to avoid to make a search in map for corresponding client connector, 

    info(20)<<"Receiv Data from offload server to client: FieldId : "<<field_->getId()<<endl ;
    packet->status = CDataPacket::NO_ERROR;


    if(this->graphEnabled)
    {
      this->graphPackage->filterId = CWorkflowGraph::getNodeSize();
      CWorkflowGraph::addNode(getContext(), "Client from offload Server Source filter", 1, false, 0, packet);
    }
    onOutputReady(std::vector<CDataPacketPtr>{packet});
    field_->getOffloadPythonSuperFilter()->receivedOffloadedData();

  }
  

} // namespace xios

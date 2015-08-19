import React from 'react'

import CommonListBox from '../commons/common_list_box.jsx'

import CommonAction from '../../actions/common_action.js'
import moment from 'moment';

import {Badge, Button, Label, Input, Modal} from 'react-bootstrap'

class StudentGradeView extends React.Component{
  constructor(props){
    super(props);
    this.state={};
  }
  
  render(){
     var detail_click = (s) => {
      console.log("show details", s);
      this.setState({showModal: true, currentSubmission: s});
    }
    var submission_mapper = (s)=>{
      
      var detail_button = (
        <button className="btn btn-block btn-primary" style={{width: 70}} onClick={detail_click.bind(null,s)}>Show</button>     
      );
      return [s.assignment.assign_num, s.status, moment(s.date).fromNow(), detail_button, s.total_score, s.late_fee, s.final_score]
    }
    
    var render_submission_result = (s) =>{
      if(!s)
        return null;
      return s.results.map(r => {
        return (
          <tr>
            <td>{r.desc}</td>
            <td>{r.output}</td>
            <td>{r.err_msg}</td>
            <td>{r.runtime}</td>
            <td>{r.points}</td>
          </tr>
        );
      });
    }
    var modalInstance = (
      <div>
        <Modal show={this.state.showModal} onHide={()=>this.setState({showModal:false})}>
          <Modal.Header closeButton>
            <Modal.Title>Submission Details</Modal.Title>
          </Modal.Header>

          <Modal.Body>
             <table className="table table-bordered"> 
              <tr>
                <td>Test Case</td>
                <td>Output</td>
                <td>Error Message</td>
                <td>Runtime</td>
                <td>Points</td>
              </tr>
              {render_submission_result(this.state.currentSubmission)}
            </table>
            <p>Total: <Badge>{this.state.currentSubmission?this.state.currentSubmission.total_score:0}</Badge></p>
            <p>Late: <Badge>{this.state.currentSubmission?this.state.currentSubmission.late_fee:0}</Badge></p>
            <p>Final: <Badge>{this.state.currentSubmission?this.state.currentSubmission.final_score:0}</Badge></p>
           
           
          </Modal.Body>

          <Modal.Footer>
            <Button onClick={()=>this.setState({showModal:false})}>Close</Button>
            
          </Modal.Footer>

        </Modal>
      </div>
    );
    return (
      <div>
        {/*header*/}
        <section className="content-header">
          <h1>
            My Grades
            <small>View my grades</small>
          </h1>
          <ol className="breadcrumb">
            <li><i className="fa fa-dashboard"></i> Home</li>
            <li>Student</li>
            <li className="active">Submissions</li>
          </ol>
        </section>
        {/*content*/}
        <div className="content body">
          <div className="row">
            <CommonListBox url="/api/grades" headers= {["Assignment", "Status", "Date", "Detail", "Total", "Late", "Final"]}
                           data_mapper={submission_mapper}
                           store_id="my_grade_list" page_size={10} />
            {modalInstance}
          </div>
          
        </div>
      </div>
    )

  }

}

export default StudentGradeView

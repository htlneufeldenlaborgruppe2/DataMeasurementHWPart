//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated from a template.
//
//     Manual changes to this file may cause unexpected behavior in your application.
//     Manual changes to this file will be overwritten if the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace GenerateTableFromDatabase.Data
{
    using System;
    using System.Collections.Generic;
    
    public partial class RoomSubject
    {
        public int fk_RoomID { get; set; }
        public int fk_TeacherID { get; set; }
        public int fk_SubjectID { get; set; }
        public int fk_ClassID { get; set; }
        public int RoomSubjectID { get; set; }
        public Nullable<bool> Test { get; set; }
        public Nullable<bool> ReplacementLesson { get; set; }
        public Nullable<int> Hour { get; set; }
        public Nullable<System.DateTime> Day { get; set; }
        public Nullable<int> fk_Teachers2ID { get; set; }
    
        public virtual Class Class { get; set; }
        public virtual Room Room { get; set; }
        public virtual Subject Subject { get; set; }
        public virtual Teacher Teacher { get; set; }
        public virtual Teacher Teacher1 { get; set; }
    }
}
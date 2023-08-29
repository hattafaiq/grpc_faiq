#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlRelationalTableModel>

#include <QObject>
#include <QDebug>

#include <QFile>
#include <iostream>
#include <memory>
#include <string>
#include "grpcpp/support/channel_arguments.h"
#include <grpcpp/grpcpp.h>
#include "gen_cloud4/Cloud.grpc.pb.h"
#include "gen_cloud4/Cloud.pb.h"

using grpc::Channel;
//using grpc::ClientAsyncResponseReader;
//using grpc::CompletionQueue;
using grpc::ClientContext;
using grpc::Status;
using grpc::ChannelArguments;
using Cloud::protokol_1;
using Cloud::protokol_2;

using Cloud::mes_client;
using Cloud::mes_server;
using Cloud::pesan_client;
using Cloud::pesan_server;

#ifndef CONTROLLER_H
#define CONTROLLER_H

#define GRPC_STATUS_CANCELLED 1

/** Unknown error.  An example of where this error may be returned is
   if a Status value received from another address space belongs to
   an error-space that is not known in this address space.  Also
   errors raised by APIs that do not return enough error information
   may be converted to this error. */
#define GRPC_STATUS_UNKNOWN 2

/** Client specified an invalid argument.  Note that this differs
   from FAILED_PRECONDITION.  INVALID_ARGUMENT indicates arguments
   that are problematic regardless of the state of the system
   (e.g., a malformed file name). */
#define GRPC_STATUS_INVALID_ARGUMENT 3

/** Deadline expired before operation could complete.  For operations
   that change the state of the system, this error may be returned
   even if the operation has completed successfully.  For example, a
   successful response from a server could have been delayed long
   enough for the deadline to expire. */
#define GRPC_STATUS_DEADLINE_EXCEEDED 4

/** Some requested entity (e.g., file or directory) was not found. */
#define GRPC_STATUS_NOT_FOUND 5

/** Some entity that we attempted to create (e.g., file or directory)
   already exists. */
#define GRPC_STATUS_ALREADY_EXISTS 6

/** The caller does not have permission to execute the specified
   operation.  PERMISSION_DENIED must not be used for rejections
   caused by exhausting some resource (use RESOURCE_EXHAUSTED
   instead for those errors).  PERMISSION_DENIED must not be
   used if the caller can not be identified (use UNAUTHENTICATED
   instead for those errors). */
#define GRPC_STATUS_PERMISSION_DENIED 7

/** The request does not have valid authentication credentials for the
   operation. */
#define GRPC_STATUS_UNAUTHENTICATED 16

/** Some resource has been exhausted, perhaps a per-user quota, or
   perhaps the entire file system is out of space. */
#define GRPC_STATUS_RESOURCE_EXHAUSTED 8

/** Operation was rejected because the system is not in a state
   required for the operation's execution.  For example, directory
   to be deleted may be non-empty, an rmdir operation is applied to
   a non-directory, etc.

   A litmus test that may help a service implementor in deciding
   between FAILED_PRECONDITION, ABORTED, and UNAVAILABLE:
    (a) Use UNAVAILABLE if the client can retry just the failing call.
    (b) Use ABORTED if the client should retry at a higher-level
        (e.g., restarting a read-modify-write sequence).
    (c) Use FAILED_PRECONDITION if the client should not retry until
        the system state has been explicitly fixed.  E.g., if an "rmdir"
        fails because the directory is non-empty, FAILED_PRECONDITION
        should be returned since the client should not retry unless
        they have first fixed up the directory by deleting files from it.
    (d) Use FAILED_PRECONDITION if the client performs conditional
        REST Get/Update/Delete on a resource and the resource on the
        server does not match the condition. E.g., conflicting
        read-modify-write on the same resource. */
#define GRPC_STATUS_FAILED_PRECONDITION 9

/** The operation was aborted, typically due to a concurrency issue
   like sequencer check failures, transaction aborts, etc.

   See litmus test above for deciding between FAILED_PRECONDITION,
   ABORTED, and UNAVAILABLE. */
#define GRPC_STATUS_ABORTED 10

/** Operation was attempted past the valid range.  E.g., seeking or
   reading past end of file.

   Unlike INVALID_ARGUMENT, this error indicates a problem that may
   be fixed if the system state changes. For example, a 32-bit file
   system will generate INVALID_ARGUMENT if asked to read at an
   offset that is not in the range [0,2^32-1], but it will generate
   OUT_OF_RANGE if asked to read from an offset past the current
   file size.

   There is a fair bit of overlap between FAILED_PRECONDITION and
   OUT_OF_RANGE.  We recommend using OUT_OF_RANGE (the more specific
   error) when it applies so that callers who are iterating through
   a space can easily look for an OUT_OF_RANGE error to detect when
   they are done. */
#define GRPC_STATUS_OUT_OF_RANGE 11

/** Operation is not implemented or not supported/enabled in this service. */
#define GRPC_STATUS_UNIMPLEMENTED 12

/** Internal errors.  Means some invariants expected by underlying
   system has been broken.  If you see one of these errors,
   something is very broken. */
#define GRPC_STATUS_INTERNAL 13

/** The service is currently unavailable.  This is a most likely a
   transient condition and may be corrected by retrying with
   a backoff. Note that it is not always safe to retry non-idempotent
   operations.

   WARNING: Although data MIGHT not have been transmitted when this
   status occurs, there is NOT A GUARANTEE that the server has not seen
   anything. So in general it is unsafe to retry on this status code
   if the call is non-idempotent.

   See litmus test above for deciding between FAILED_PRECONDITION,
   ABORTED, and UNAVAILABLE. */
#define GRPC_STATUS_UNAVAILABLE 14

/** Unrecoverable data loss or corruption. */
#define GRPC_STATUS_DATA_LOSS = 15

class controller
{
public:
    controller();
    int flag_sukses;
//    int flag_pengiriman;
    QVector<int>data_n[7];
//    int counter_s;
//    int conter_loop;
    QByteArray data_utama;
    QString initial_rute;
    QStringList list_rute;
    QString get_table_name(int tipe);
    QSqlDatabase db;
    QString con_name;
    int id_database;

    QStringList rute_baru;

    QStringList cacah_data_name;

    //-------------persiapan data ke 2-------//
    QStringList aset_info_server;//list aset utuh seluruh data balik server
    QStringList aset_info_tampil;
    QVector<int> c_id_param_lama;
    QVector<int> c_id_masuk_lama;
    QVector<int> c_tipe_param;
    QVector<int> c_id_rute_lama;
    QVector<int> c_time;
    QVector<int> c_siklus;
    QStringList c_rute;
    QByteArrayList c_all_rute_param;
    QByteArrayList c_all_data;

    int alarm_message;
    int alarm_message_data;
    QString pesan_alarm;

    void CallServer(std::string pesan, int flag, std::string server_alamat,int count, int jumlah);
    void isi_pesan();
    void initial_database();
    void cari_induk_param(int p_id_aset);
    void emit_gas_kirim(int counter, int maks);
    int flag_emit_cukup;
    int counter_pesan;

private:
    void cari_induk_paramm(int parameter, int tipe);
    void cari_induk(int p_id_aset);
    void mulai_cari(QSqlQuery *query);


//public slots:
//    void counter();
//signals:
//    void gas_kirim();

};

#endif // CONTROLLER_H

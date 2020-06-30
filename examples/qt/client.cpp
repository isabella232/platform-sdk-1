// AirMap Platform SDK
// Copyright © 2018 AirMap, Inc. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//   http://www.apache.org/licenses/LICENSE-2.0
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an AS IS BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#include "client.h"

#include <airmap/qt/client.h>
#include <airmap/qt/logger.h>
#include <airmap/types.h>

#include <airmap/authenticator.h>

#include <QCoreApplication>
#include <QThread>

namespace {

constexpr const char* api_key =
      "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJjcmVkZW50aWFsX2lkIjoiY3JlZGVudGlhbHxMZEV3WG9XU1pueDY5NVN2YXpvOWdmM21nRGJ5IiwiYXBwbGljYXRpb25faWQiOiJhcHBsaWNhdGlvbnxMRzlkcFF5ZjNuQXAwMlRNWHBwWkdGTEtYeGFkIiwib3JnYW5pemF0aW9uX2lkIjoiZGV2ZWxvcGVyfG04NHdLd0pIMk81QVg3aHhCcHB2UUl3ZExZIiwiaWF0IjoxNTkwNzAwMTM2fQ.SC5S_B5EzHQ_P6eS-MFEqjBwvAgTO5bQ_tymOxWtKy4";
}  // namespace

#include <QMetaType>

Q_DECLARE_METATYPE(airmap::Aircraft)
Q_DECLARE_METATYPE(airmap::Airspace)
Q_DECLARE_METATYPE(airmap::Credentials)
Q_DECLARE_METATYPE(airmap::DateTime)
Q_DECLARE_METATYPE(airmap::Error)
Q_DECLARE_METATYPE(airmap::FlightPlan)
Q_DECLARE_METATYPE(airmap::Flight)
Q_DECLARE_METATYPE(airmap::Geometry)
Q_DECLARE_METATYPE(airmap::Pilot)
Q_DECLARE_METATYPE(airmap::Rule)
Q_DECLARE_METATYPE(airmap::RuleSet)
Q_DECLARE_METATYPE(airmap::RuleSet::Rule)
Q_DECLARE_METATYPE(airmap::Status::Advisory)
Q_DECLARE_METATYPE(airmap::Status::Wind)
Q_DECLARE_METATYPE(airmap::Status::Weather)
Q_DECLARE_METATYPE(airmap::Status::Report)
Q_DECLARE_METATYPE(airmap::Telemetry::Position)
Q_DECLARE_METATYPE(airmap::Telemetry::Speed)
Q_DECLARE_METATYPE(airmap::Telemetry::Attitude)
Q_DECLARE_METATYPE(airmap::Telemetry::Barometer)
Q_DECLARE_METATYPE(airmap::Optional<airmap::Telemetry::Update>)
Q_DECLARE_METATYPE(airmap::Token::Type)
Q_DECLARE_METATYPE(airmap::Token::Anonymous)
Q_DECLARE_METATYPE(airmap::Token::OAuth)
Q_DECLARE_METATYPE(airmap::Token::Refreshed)
Q_DECLARE_METATYPE(airmap::Token)
Q_DECLARE_METATYPE(airmap::Traffic::Update::Type)
Q_DECLARE_METATYPE(airmap::Traffic::Update)
Q_DECLARE_METATYPE(airmap::Version)

void register_types() {
  qRegisterMetaType<airmap::Aircraft>("Aircraft");
  qRegisterMetaType<airmap::Airspace>("Airspace");
  qRegisterMetaType<airmap::Credentials>("Credentials");
  qRegisterMetaType<airmap::DateTime>("DateTime");
  qRegisterMetaType<airmap::Error>("Error");
  qRegisterMetaType<airmap::FlightPlan>("FlightPlan");
  qRegisterMetaType<airmap::Flight>("Flight");
  qRegisterMetaType<airmap::Geometry>("Geometry");
  qRegisterMetaType<airmap::Pilot>("Pilot");
  qRegisterMetaType<airmap::Rule>("Rule");
  qRegisterMetaType<airmap::RuleSet>("RuleSet");
  qRegisterMetaType<airmap::RuleSet::Rule>("RuleSet::Rule");
  qRegisterMetaType<airmap::Status::Advisory>("Status::Advisory");
  qRegisterMetaType<airmap::Status::Wind>("Status::Wind");
  qRegisterMetaType<airmap::Status::Weather>("Status::Weather");
  qRegisterMetaType<airmap::Status::Report>("Status::Report");
  qRegisterMetaType<airmap::Telemetry::Position>("Telemetry::Position");
  qRegisterMetaType<airmap::Telemetry::Speed>("Telemetry::Speed");
  qRegisterMetaType<airmap::Telemetry::Attitude>("Telemetry::Attitude");
  qRegisterMetaType<airmap::Telemetry::Barometer>("Telemetry::Barometer");
  qRegisterMetaType<airmap::Optional<airmap::Telemetry::Update>>("Optional<Telemetry::Update>");
  qRegisterMetaType<airmap::Token::Type>("Token::Type");
  qRegisterMetaType<airmap::Token::Anonymous>("Token::Anonymous");
  qRegisterMetaType<airmap::Token::OAuth>("Token::OAuth");
  qRegisterMetaType<airmap::Token::Refreshed>("Token::Refreshed");
  qRegisterMetaType<airmap::Token>("Token");
  qRegisterMetaType<airmap::Traffic::Update::Type>("Traffic::Update::Type");
  qRegisterMetaType<airmap::Traffic::Update>("Traffic::Update");
  qRegisterMetaType<airmap::Version>("Version");

  //TODO: what's the difference beween registering airmap::Aircraft named 'Aircraft' and 'airmap::Aircraft'?
  qRegisterMetaType<airmap::Aircraft>("airmap::Aircraft");
  qRegisterMetaType<airmap::Airspace>("airmap::Airspace");
  qRegisterMetaType<airmap::Credentials>("airmap::Credentials");
  qRegisterMetaType<airmap::DateTime>("airmap::DateTime");
  qRegisterMetaType<airmap::Error>("airmap::Error");
  qRegisterMetaType<airmap::FlightPlan>("airmap::FlightPlan");
  qRegisterMetaType<airmap::Flight>("airmap::Flight");
  qRegisterMetaType<airmap::Geometry>("airmap::Geometry");
  qRegisterMetaType<airmap::Pilot>("airmap::Pilot");
  qRegisterMetaType<airmap::Rule>("airmap::Rule");
  qRegisterMetaType<airmap::RuleSet>("airmap::RuleSet");
  qRegisterMetaType<airmap::RuleSet::Rule>("airmap::RuleSet::Rule");
  qRegisterMetaType<airmap::Status::Advisory>("airmap::Advisory");
  qRegisterMetaType<airmap::Status::Wind>("airmap::Wind");
  qRegisterMetaType<airmap::Status::Weather>("airmap::Weather");
  qRegisterMetaType<airmap::Status::Report>("airmap::Report");
  qRegisterMetaType<airmap::Telemetry::Position>("airmap::Telemetry::Position");
  qRegisterMetaType<airmap::Telemetry::Speed>("airmap::Telemetry::Speed");
  qRegisterMetaType<airmap::Telemetry::Attitude>("airmap::Telemetry::Attitude");
  qRegisterMetaType<airmap::Telemetry::Barometer>("airmap::Telemetry::Barometer");
  qRegisterMetaType<airmap::Optional<airmap::Telemetry::Update>>("airmap::Optional<airmap::Telemetry::Update>");
  qRegisterMetaType<airmap::Token::Type>("airmap::Token::Type");
  qRegisterMetaType<airmap::Token::Anonymous>("airmap::Token::Anonymous");
  qRegisterMetaType<airmap::Token::OAuth>("airmap::Token::OAuth");
  qRegisterMetaType<airmap::Token::Refreshed>("airmap::Token::Refreshed");
  qRegisterMetaType<airmap::Token>("airmap::Token");
  qRegisterMetaType<airmap::Traffic::Update::Type>("airmap::Traffic::Update::Type");
  qRegisterMetaType<airmap::Traffic::Update>("airmap::Traffic::Update");
  qRegisterMetaType<airmap::Version>("airmap::Version");
}

class QtMainThreadScheduler : public QObject,
                              public airmap::Context::Scheduler,
                              public std::enable_shared_from_this<QtMainThreadScheduler>
{
  struct Event : public QEvent {

      static Type registered_type() {
        static const Type rt = static_cast<Type>(registerEventType());
        return rt;
      }

      explicit Event(const std::function<void()>& task)
      : QEvent{registered_type()},
        task_(task)
      {}

      std::function<void()> task_;
  };

  public:
    void schedule(const std::function<void()>& task) override {
      QCoreApplication::postEvent(this, new Event{[task]() { task(); }});
    }

    bool event(QEvent* event) {
      assert(QCoreApplication::instance());
      assert(QThread::currentThread() == QCoreApplication::instance()->thread());

      if (event->type() == Event::registered_type()) {
        event->accept();

        if (auto e = dynamic_cast<Event*>(event)) {
          e->task_();
        }
        return true;
      }
      return false;
    }
};

int main(int argc, char** argv) {
  QCoreApplication app{argc, argv};
  auto qlogger = std::make_shared<airmap::qt::Logger>();

  qlogger->logging_category().setEnabled(QtDebugMsg, true);
  qlogger->logging_category().setEnabled(QtInfoMsg, true);
  qlogger->logging_category().setEnabled(QtWarningMsg, true);

  auto credentials    = airmap::Credentials{};
  credentials.api_key = api_key;
  auto dlogger        = std::make_shared<airmap::qt::DispatchingLogger>(qlogger);
  auto configuration  = airmap::Client::default_production_configuration(credentials);

  register_types();
  auto context = airmap::Context::create(qlogger, std::make_shared<QtMainThreadScheduler>());

  if (!context) {
    qCritical("Failed to establish queued signal-slot connections, exiting with error");
    exit(1);
  } else {
    context.value()->create_client_with_configuration(
      configuration, [configuration](const auto& result) {
        if (result) {
          auto client = result.value();
          qInfo("Successfully created AirMap client");
          airmap::Authenticator::AuthenticateAnonymously::Params params;
          params.id = "qt client";
          client->authenticator().authenticate_anonymously(params, [client](const auto& result) {
            if (result) {
              qInfo("Successfully authenticated with AirMap: %s", result.value().id.c_str());
              QCoreApplication::exit(0);
            } else {
              qCritical("Failed to authenticate with AirMap due to: %s", result.error());
              QCoreApplication::exit(1);
            }
          });
        } else {
          qCritical("Failed to create AirMap client due to: %s", result.error());
          QCoreApplication::exit(1);
        }
     });
  }

  auto client  = new airmap::examples::qt::Client{&app};
  if (!client->test()) {
    qCritical("Failed to establish queued signal-slot connections, exiting with error");
    QCoreApplication::exit(1);
  }
  auto context_runner = std::thread{[context]() { context.value()->run(); }};
  return app.exec();
}

airmap::examples::qt::Client::Client(QObject* parent) : QObject{parent} {
}

bool airmap::examples::qt::Client::test() {
  bool result = true;
  result &= static_cast<bool>(
      connect(this, SIGNAL(sig_(const Aircraft&)), this, SLOT(slot_(const Aircraft&)), Qt::QueuedConnection));
  result &= static_cast<bool>(
      connect(this, SIGNAL(sig_(const Airspace&)), this, SLOT(slot_(const Airspace&)), Qt::QueuedConnection));
  result &= static_cast<bool>(
      connect(this, SIGNAL(sig_(const Credentials&)), this, SLOT(slot_(const Credentials&)), Qt::QueuedConnection));
  result &= static_cast<bool>(
      connect(this, SIGNAL(sig_(const DateTime&)), this, SLOT(slot_(const DateTime&)), Qt::QueuedConnection));
  result &= static_cast<bool>(
      connect(this, SIGNAL(sig_(const FlightPlan&)), this, SLOT(slot_(const FlightPlan&)), Qt::QueuedConnection));
  result &= static_cast<bool>(
      connect(this, SIGNAL(sig_(const Flight&)), this, SLOT(slot_(const Flight&)), Qt::QueuedConnection));
  result &= static_cast<bool>(
      connect(this, SIGNAL(sig_(const Geometry&)), this, SLOT(slot_(const Geometry&)), Qt::QueuedConnection));
  result &= static_cast<bool>(
      connect(this, SIGNAL(sig_(const Pilot&)), this, SLOT(slot_(const Pilot&)), Qt::QueuedConnection));
  result &=
      static_cast<bool>(connect(this, SIGNAL(sig_(const Rule&)), this, SLOT(slot_(const Rule&)), Qt::QueuedConnection));
  result &= static_cast<bool>(
      connect(this, SIGNAL(sig_(const RuleSet&)), this, SLOT(slot_(const RuleSet&)), Qt::QueuedConnection));
  result &= static_cast<bool>(
      connect(this, SIGNAL(sig_(const RuleSet::Rule&)), this, SLOT(slot_(const RuleSet::Rule&)), Qt::QueuedConnection));
  result &= static_cast<bool>(connect(this, SIGNAL(sig_(const Status::Advisory&)), this,
                                      SLOT(slot_(const Status::Advisory&)), Qt::QueuedConnection));
  result &= static_cast<bool>(
      connect(this, SIGNAL(sig_(const Status::Wind&)), this, SLOT(slot_(const Status::Wind&)), Qt::QueuedConnection));
  result &= static_cast<bool>(connect(this, SIGNAL(sig_(const Status::Weather&)), this,
                                      SLOT(slot_(const Status::Weather&)), Qt::QueuedConnection));
  result &= static_cast<bool>(connect(this, SIGNAL(sig_(const Status::Report&)), this,
                                      SLOT(slot_(const Status::Report&)), Qt::QueuedConnection));
  result &= static_cast<bool>(connect(this, SIGNAL(sig_(const Telemetry::Position&)), this,
                                      SLOT(slot_(const Telemetry::Position&)), Qt::QueuedConnection));
  result &= static_cast<bool>(connect(this, SIGNAL(sig_(const Telemetry::Speed&)), this,
                                      SLOT(slot_(const Telemetry::Speed&)), Qt::QueuedConnection));
  result &= static_cast<bool>(connect(this, SIGNAL(sig_(const Telemetry::Attitude&)), this,
                                      SLOT(slot_(const Telemetry::Attitude&)), Qt::QueuedConnection));
  result &= static_cast<bool>(connect(this, SIGNAL(sig_(const Telemetry::Barometer&)), this,
                                      SLOT(slot_(const Telemetry::Barometer&)), Qt::QueuedConnection));
  result &= static_cast<bool>(connect(this, SIGNAL(sig_(const Optional<Telemetry::Update>&)), this,
                                      SLOT(slot_(const Optional<Telemetry::Update>&)), Qt::QueuedConnection));
  result &= static_cast<bool>(
      connect(this, SIGNAL(sig_(const Token::Type&)), this, SLOT(slot_(const Token::Type&)), Qt::QueuedConnection));
  result &= static_cast<bool>(connect(this, SIGNAL(sig_(const Token::Anonymous&)), this,
                                      SLOT(slot_(const Token::Anonymous&)), Qt::QueuedConnection));
  result &= static_cast<bool>(
      connect(this, SIGNAL(sig_(const Token::OAuth&)), this, SLOT(slot_(const Token::OAuth&)), Qt::QueuedConnection));
  result &= static_cast<bool>(connect(this, SIGNAL(sig_(const Token::Refreshed&)), this,
                                      SLOT(slot_(const Token::Refreshed&)), Qt::QueuedConnection));
  result &= static_cast<bool>(
      connect(this, SIGNAL(sig_(const Token&)), this, SLOT(slot_(const Token&)), Qt::QueuedConnection));
  result &= static_cast<bool>(connect(this, SIGNAL(sig_(const Traffic::Update::Type&)), this,
                                      SLOT(slot_(const Traffic::Update::Type&)), Qt::QueuedConnection));
  result &= static_cast<bool>(connect(this, SIGNAL(sig_(const Traffic::Update&)), this,
                                      SLOT(slot_(const Traffic::Update&)), Qt::QueuedConnection));
  result &= static_cast<bool>(
      connect(this, SIGNAL(sig_(const Version&)), this, SLOT(slot_(const Version&)), Qt::QueuedConnection));

  return result;
}

void airmap::examples::qt::Client::slot_(const Aircraft&) {
}
void airmap::examples::qt::Client::slot_(const Airspace&) {
}
void airmap::examples::qt::Client::slot_(const Credentials&) {
}
void airmap::examples::qt::Client::slot_(const DateTime&) {
}
void airmap::examples::qt::Client::slot_(const FlightPlan&) {
}
void airmap::examples::qt::Client::slot_(const Flight&) {
}
void airmap::examples::qt::Client::slot_(const Geometry&) {
}
void airmap::examples::qt::Client::slot_(const Pilot&) {
}
void airmap::examples::qt::Client::slot_(const Rule&) {
}
void airmap::examples::qt::Client::slot_(const RuleSet&) {
}
void airmap::examples::qt::Client::slot_(const RuleSet::Rule&) {
}
void airmap::examples::qt::Client::slot_(const Status::Advisory&) {
}
void airmap::examples::qt::Client::slot_(const Status::Wind&) {
}
void airmap::examples::qt::Client::slot_(const Status::Weather&) {
}
void airmap::examples::qt::Client::slot_(const Status::Report&) {
}
void airmap::examples::qt::Client::slot_(const Telemetry::Position&) {
}
void airmap::examples::qt::Client::slot_(const Telemetry::Speed&) {
}
void airmap::examples::qt::Client::slot_(const Telemetry::Attitude&) {
}
void airmap::examples::qt::Client::slot_(const Telemetry::Barometer&) {
}
void airmap::examples::qt::Client::slot_(const Optional<Telemetry::Update>&) {
}
void airmap::examples::qt::Client::slot_(const Token::Type&) {
}
void airmap::examples::qt::Client::slot_(const Token::Anonymous&) {
}
void airmap::examples::qt::Client::slot_(const Token::OAuth&) {
}
void airmap::examples::qt::Client::slot_(const Token::Refreshed&) {
}
void airmap::examples::qt::Client::slot_(const Token&) {
}
void airmap::examples::qt::Client::slot_(const Traffic::Update::Type&) {
}
void airmap::examples::qt::Client::slot_(const Traffic::Update&) {
}
void airmap::examples::qt::Client::slot_(const Version&) {
}
